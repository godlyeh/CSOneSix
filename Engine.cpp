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

	if (pLocal->index == pEntity->index)
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

void EngineHelper::AngleVectors(float *flAngles, float *flForward, float *flRight, float *flUp)
{
	float v16 = (float)sin(flAngles[0] * (M_PI / 180));
	float v15 = (float)cos(flAngles[0] * (M_PI / 180));

	float v12 = (float)sin(flAngles[1] * (M_PI / 180));
	float v13 = (float)cos(flAngles[1] * (M_PI / 180));

	float v11 = (float)sin(flAngles[2] * (M_PI / 180));
	float v14 = (float)cos(flAngles[2] * (M_PI / 180));

	if (flForward)
	{
		flForward[0] = v15 * v13;
		flForward[1] = v15 * v12;
		flForward[2] = -v16;
	}
	if (flRight)
	{
		float v8 = v11 * v16;
		flRight[0] = v14 * v12 - v8 * v13;
		flRight[1] = (v8 * v12 + v14 * v13) * -1.0f;
		flRight[2] = v11 * v15 * -1.0f;
	}
	if (flUp)
	{
		float v10 = v14 * v16;
		flUp[0] = v10 * v13 + v11 * v12;
		flUp[1] = v10 * v12 - v11 * v13;
		flUp[2] = v14 * v15;
	}
}

void EngineHelper::VectorAngles(const float *flForward, float *flAngles)
{
	double tmp, yaw, pitch;
	if (flForward[1] == 0 && flForward[0] == 0)
	{
		if (flForward[2]>0)
			pitch = 90.0;
		else
			pitch = 270.0;
	}
	else
		yaw = (double)(atan2(flForward[1], flForward[0])*180.0 / M_PI);
	if (yaw<0)
		yaw += 360.0;
	tmp = (double)sqrt(flForward[0] * flForward[0] + flForward[1] * flForward[1]);
	pitch = (double)(atan2(flForward[2], (float)tmp)*180.0 / M_PI);
	flAngles[0] = (float)pitch;
	flAngles[1] = (float)yaw;
	flAngles[2] = 0;
}

void EngineHelper::VectorToViewangles(float *flOrigin, float *flOut)
{
	Vector vDest, vAngles;
	VectorSubtract(flOrigin, g_Local.EyePosition, vDest);
	VectorAngles(vDest, vAngles);
	vAngles[0] *= -1.0f;
	BoundAngles(vAngles);
	VectorCopy(vAngles, flOut);
}

long double EngineHelper::VectorNormalize(float *flAngles)
{
	long double ldRet = sqrt(flAngles[0] * flAngles[0] + flAngles[1] * flAngles[1] + flAngles[2] * flAngles[2]);

	if (ldRet != 0.0f)
	{
		flAngles[0] = flAngles[0] * (1.0f / (float)ldRet);
		flAngles[1] = flAngles[1] * (1.0f / (float)ldRet);
		flAngles[2] = flAngles[2] * (1.0f / (float)ldRet);
	}

	return ldRet;
}

void EngineHelper::BoundAngles(float *flViewAngles)
{
	for (int i = 0; i < 2; ++i)
	{
		if (flViewAngles[i] > 180.0f) flViewAngles[i] -= 360.0f;
		if (flViewAngles[i] < -180.0f) flViewAngles[i] += 360.0f;
	}
	flViewAngles[2] = 0;
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

// Trace
void EngineHelper::MP_TraceLine(float *vecSrc, float *vecEnd, int ignore, pmtrace_t *tr)
{
	float tmpSrc[3], length, length1, length2, vecDir[3];

	vecDir[0] = vecEnd[0] - vecSrc[0];
	vecDir[1] = vecEnd[1] - vecSrc[1];
	vecDir[2] = vecEnd[2] - vecSrc[2];

	length = VectorLength(vecDir);

	vecDir[0] /= length;
	vecDir[1] /= length;
	vecDir[2] /= length;

	if (vecSrc[0] == vecEnd[0] && vecSrc[1] == vecEnd[1] && vecSrc[2] == vecEnd[2])
	{
		memset(tr, 0, sizeof(pmtrace_t));

		tr->endpos[0] = vecEnd[0];
		tr->endpos[1] = vecEnd[1];
		tr->endpos[2] = vecEnd[2];

		tr->fraction = 1.0f;

		return;
	}

	g_oEngine.pEventAPI->EV_SetTraceHull(2);
	g_oEngine.pEventAPI->EV_PlayerTrace(vecSrc, vecEnd, PM_GLASS_IGNORE, -1, tr);

	if (tr->fraction == 0 && tr->startsolid && !tr->allsolid)
	{
		tmpSrc[0] = vecSrc[0];
		tmpSrc[1] = vecSrc[1];
		tmpSrc[2] = vecSrc[2];

		while (!tr->allsolid && tr->fraction == 0)
		{
			tmpSrc[0] += vecDir[0];
			tmpSrc[1] += vecDir[1];
			tmpSrc[2] += vecDir[2];

			g_oEngine.pEventAPI->EV_SetTraceHull(2);
			g_oEngine.pEventAPI->EV_PlayerTrace(tmpSrc, vecEnd, PM_GLASS_IGNORE, -1, tr);
		}

		if (!tr->allsolid && tr->fraction != 1.0)
		{
			tmpSrc[0] = vecEnd[0] - vecSrc[0];
			tmpSrc[1] = vecEnd[1] - vecSrc[1];
			tmpSrc[2] = vecEnd[2] - vecSrc[2];

			length1 = VectorLength(tmpSrc);

			tmpSrc[0] = tr->endpos[0] - vecSrc[0];
			tmpSrc[1] = tr->endpos[1] - vecSrc[1];
			tmpSrc[2] = tr->endpos[2] - vecSrc[2];

			length2 = VectorLength(tmpSrc);

			tr->fraction = length2 / length1;

			tr->startsolid = 1;
		}
	}

	if (tr->allsolid)
		tr->fraction = 1.0f;
}

bool EngineHelper::IsPointVisible(float* Point)
{
	pmtrace_t Trace;
	MP_TraceLine(g_Local.EyePosition, Point, g_Local.Index, &Trace);
	return Trace.fraction == 1.0f;
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