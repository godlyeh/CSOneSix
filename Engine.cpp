// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
cl_enginefunc_t* g_pEngine;
cl_enginefunc_t g_oEngine;
net_api_t* g_pNetApi;
client_sprite_t* g_pSpriteList;
SCREENINFO g_ScreenInfo;
HSPRITE* g_pSprite;
ViewMatrix* g_pViewMatrix;
// ===================================================================================


// ===================================================================================
// Engine helper

// Client info
bool EngineHelper::IsConnected()
{
	g_pNetApi->Status(&NetStatus);
	return (NetStatus.connected != 0);
}

void EngineHelper::UpdateScreenInfo()
{
	g_ScreenInfo.iSize = sizeof(SCREENINFO);
	g_oEngine.pfnGetScreenInfo(&g_ScreenInfo);
}

bool EngineHelper::ValidEntity(int EntityID)
{
	cl_entity_t* pLocal = g_oEngine.GetLocalPlayer();
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(EntityID);

	if (!pLocal || !pEntity)
		return false;

	if (pEntity->curstate.messagenum < pLocal->curstate.messagenum)
		return false;

	if (pEntity->curstate.solid != 1 && pEntity->curstate.solid != 3)
		return false;

	return true;
}

bool EngineHelper::ValidPlayer(int PlayerID)
{
	if (PlayerID < 0 || PlayerID > MAX_CLIENTS)
		return false;

	if (ValidEntity(PlayerID) == false)
		return false;

	cl_entity_t* pLocal = g_oEngine.GetLocalPlayer();
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(PlayerID);

	if (pEntity->player == FALSE)
		return false;

	if (pLocal->index == pEntity->index)
		return false;

	if (pEntity->curstate.solid != 3)
		return false;

	if (pLocal->curstate.solid != 3 && pLocal->curstate.iuser1 == 4 && pLocal->curstate.iuser2 == pEntity->index)
		return false;

	return true;
}

// Engine math
bool EngineHelper::WorldToScreen(float* Origin, float* Out)
{
	Out[0] = g_pViewMatrix[0][0] * Origin[0] + g_pViewMatrix[1][0] * Origin[1] + g_pViewMatrix[2][0] * Origin[2] + g_pViewMatrix[3][0];
	Out[1] = g_pViewMatrix[0][1] * Origin[0] + g_pViewMatrix[1][1] * Origin[1] + g_pViewMatrix[2][1] * Origin[2] + g_pViewMatrix[3][1];
	Out[2] = g_pViewMatrix[0][3] * Origin[0] + g_pViewMatrix[1][3] * Origin[1] + g_pViewMatrix[2][3] * Origin[2] + g_pViewMatrix[3][3];

	if (Out[2] != 0.0f)
	{
		float flTmp = 1.0f / Out[2];
		Out[0] *= flTmp;
		Out[1] *= flTmp;
	}

	if (Out[2] > 0.0f)
	{
		Out[0] = (Out[0] + 1.0f) * (g_ScreenInfo.iWidth / 2);
		Out[1] = (-Out[1] + 1.0f) * (g_ScreenInfo.iHeight / 2);
		return true;
	}
	return false;
}

// Init
void EngineHelper::InitHUD()
{
	g_pNetApi = g_pEngine->pNetAPI;
	dwHUDPointer = Utility->FindPattern("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 85 C0 74 59");
	g_pSpriteList = *(client_sprite_t**)(dwHUDPointer + 0xC); // HUD->m_pSpriteList
	g_pSprite = *(HSPRITE**)(dwHUDPointer + 0x178); // HUD->m_rghSprites
	UpdateScreenInfo();

	Utility->DeleteLog("HUD.txt");
	Utility->Log("HUD.txt", "HUD Pointer: 0x%p\n", dwHUDPointer);

	Utility->Log("HUD.txt", "HUD Sprite List: 0x%p\n", g_pSpriteList);
}

void EngineHelper::Initialize()
{
	InitHUD();

	strcpy_s(g_Local.LevelName, g_oEngine.pfnGetLevelName());

	g_pViewMatrix = (ViewMatrix*)Utility->FindPattern("hw.dll", "8D BF ? ? ? ? C7 07 ? ? ? ?");
	Utility->DeleteLog("Engine.txt");
	Utility->Log("Engine.txt", "ViewMatrix: 0x%p\n", g_pViewMatrix);
}
// ===================================================================================


// ===================================================================================
// Engine table hook
void HookEngineTable()
{
	DWORD dwEnginePointer = Utility->FindPattern("client.dll", "BF ? ? ? ? F3 A5");

	Utility->DeleteLog("Engine.txt");
	Utility->Log("Engine.txt", "Engine Pointer: 0x%p (Module: 0x%p)\n", dwEnginePointer, Utility->CalcModuleOffset(dwEnginePointer));

	g_pEngine = (cl_enginefunc_t*)dwEnginePointer;
	memcpy(&g_oEngine, g_pEngine, sizeof(cl_enginefunc_t));

	EngineHelper::Initialize();
}

void UnhookEngineTable()
{
	memcpy(g_pEngine, &g_oEngine, sizeof(cl_enginefunc_t));
}
// ===================================================================================