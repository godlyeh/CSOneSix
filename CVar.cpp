// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
hl_cvar_t* g_pCVarList;
// ===================================================================================


// ===================================================================================
// CVar list hook
void HookCVarList()
{
	DWORD dwCVarListPointer = Utility->FindPattern("hw.dll", "8B 35 ? ? ? ? 83 C4 04 85 F6 74 1A");
	dwCVarListPointer = *(PDWORD)dwCVarListPointer;

	Utility->DeleteLog("CVars.txt");
	Utility->Log("CVars.txt", "CVar List Pointer: 0x%p\n", dwCVarListPointer);

	g_pCVarList = (hl_cvar_t*)dwCVarListPointer;

	while (g_pCVarList)
	{
		Utility->Log("CVars.txt", " [CVarList][0x%p] %s = 0x%p (%.2f)\n", g_pCVarList, g_pCVarList->Name, g_pCVarList->Function, g_pCVarList->Value);
		g_pCVarList = g_pCVarList->Next;
	}

	g_pCVarList = (hl_cvar_t*)dwCVarListPointer;
}

void UnhookCVarList()
{
	
}
// ===================================================================================