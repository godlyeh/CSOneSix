// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
event_t* g_pEventList;
// ===================================================================================


// ===================================================================================
// Event list hook
void HookEventList()
{
	DWORD dwEventListPointer = Utility->FindPattern("hw.dll", "8B 35 ? ? ? ? 57 8B 7D 08");
	dwEventListPointer = *(PDWORD)dwEventListPointer;

	Utility->DeleteLog("Events.txt");
	Utility->Log("Events.txt", "Event List Pointer: 0x%p (Module: 0x%p)\n", dwEventListPointer, Utility->CalcModuleOffset(dwEventListPointer));

	g_pEventList = (event_t*)dwEventListPointer;

	while (g_pEventList)
	{
		Utility->Log("Events.txt", " [EventList][0x%p] %s = 0x%p (Module: 0x%p)\n", g_pEventList, g_pEventList->Name, g_pEventList->Function, Utility->CalcModuleOffset((DWORD)g_pEventList));
		g_pEventList = g_pEventList->Next;
	}

	g_pEventList = (event_t*)dwEventListPointer;
}

void UnhookEventList()
{

}
// ===================================================================================