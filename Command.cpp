// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
hl_command_t* g_pCommandList;
// ===================================================================================


// ===================================================================================
// Command list hook
void HookCommandList()
{
	DWORD dwCommandListPointer = Utility->FindPattern("hw.dll", "8B 35 ? ? ? ? 85 F6 74 17");
	dwCommandListPointer = *(PDWORD)dwCommandListPointer;

	Utility->DeleteLog("Commands.txt");
	Utility->Log("Commands.txt", "Command List Pointer: 0x%p (Module: 0x%p)\n", dwCommandListPointer, Utility->CalcModuleOffset(dwCommandListPointer));

	g_pCommandList = (hl_command_t*)dwCommandListPointer;

	while (g_pCommandList)
	{
		Utility->Log("Commands.txt", " [CommandList][0x%p] %s = 0x%p (Module: 0x%p)\n", g_pCommandList, g_pCommandList->Name, g_pCommandList->Function, Utility->CalcModuleOffset((DWORD)g_pCommandList));
		g_pCommandList = g_pCommandList->Next;
	}

	g_pCommandList = (hl_command_t*)dwCommandListPointer;
}

void UnhookCommandList()
{
	
}
// ===================================================================================