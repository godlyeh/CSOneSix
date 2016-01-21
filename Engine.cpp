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
HSPRITE* g_pSprite;
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