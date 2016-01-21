// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
engine_studio_api_t* g_pStudio;
engine_studio_api_t g_oStudio;
// ===================================================================================


// ===================================================================================
// Studio table hook
void HookStudioTable()
{
	DWORD dwStudioPointer = Utility->FindPattern("client.dll", "BF ? ? ? ? C7 00 ? ? ? ? F3 A5");

	Utility->DeleteLog("Studio.txt");
	Utility->Log("Studio.txt", "Studio Pointer: 0x%p (Module: 0x%p)\n", dwStudioPointer, Utility->CalcModuleOffset(dwStudioPointer));

	g_pStudio = (engine_studio_api_t*)dwStudioPointer;
	memcpy(&g_oStudio, g_pStudio, sizeof(engine_studio_api_t));
}

void UnhookStudioTable()
{
	memcpy(g_pStudio, &g_oStudio, sizeof(engine_studio_api_t));
}
// ===================================================================================