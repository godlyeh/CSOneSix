// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
char g_szHackDir[MAX_PATH] = "\0";
// ===================================================================================


// ===================================================================================
// Hook hack
void Hook()
{
	Utility->GenerateModuleList();

	HookEngineTable(); // Hook engine table first
	HookStudioTable();
	HookCommandList();
	HookCVarList();
	HookKeyBindings();
	HookEventList();
	HookUserMsgList();
	HookExportTable();
}
// ===================================================================================


// ===================================================================================
// Unhook hack
void Unhook()
{
	UnhookEngineTable(); // Hook engine table first
	UnhookStudioTable();
	UnhookCommandList();
	UnhookCVarList();
	UnhookKeyBindings();
	UnhookEventList();
	UnhookUserMsgList();
	UnhookExportTable();
}
// ===================================================================================


// ===================================================================================
// DllMain
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwCallReason, LPVOID lpReserved)
{
	if (dwCallReason == DLL_PROCESS_ATTACH)
	{
		// Get file path
		GetModuleFileName(hModule, g_szHackDir, MAX_PATH);
		*(strrchr(g_szHackDir, '\\') + 1) = '\0';

		// Hook
		Hook();

		return TRUE;
	}

	if (dwCallReason == DLL_PROCESS_DETACH)
	{
		Unhook();
	}

	return FALSE;
}
// ===================================================================================