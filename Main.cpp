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
void ConsoleFunc(std::string ConsoleCommand)
{
	MessageBox(0, "Hey", 0, 0);
}

void HookHack()
{
	Utility->GenerateModuleList();
	Console::AddCommand("setvar", ConsoleFunc);

	HookEngineTable(); // Hook engine table first
	Variable::Initialize();
	InitializePlayerInfos();

	HookStudioTable();
	HookCommandList();
	HookCVarList();
	HookKeyBindings();
	HookEventList();
	HookUserMsgList();
	HookExportTable();
	HookOpenGLTable();
	//HookSound();

	Hook::Apply();
}
// ===================================================================================


// ===================================================================================
// Unhook hack
void UnhookHack()
{
	Variable::Save("Variables.cfg");

	Hook::Remove();

	UnhookEngineTable();
	UnhookStudioTable();
	UnhookCommandList();
	UnhookCVarList();
	UnhookKeyBindings();
	UnhookEventList();
	//UnhookUserMsgList();
	UnhookExportTable();
	//UnhookOpenGLTable();
	//UnhookSound();
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
		HookHack();

		return TRUE;
	}

	if (dwCallReason == DLL_PROCESS_DETACH)
	{
		// Unhook hack
		UnhookHack();
	}

	return FALSE;
}
// ===================================================================================