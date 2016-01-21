// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
kblist_t* g_pKeyBinding;
// ===================================================================================


// ===================================================================================
// Key binding hook
void HookKeyBindings()
{
	DWORD dwKeybindingPointer = Utility->FindPattern("client.dll", "8B 35 ? ? ? ? 85 F6 57");
	dwKeybindingPointer = *(PDWORD)dwKeybindingPointer;

	Utility->DeleteLog("KeyBinding.txt");
	Utility->Log("KeyBinding.txt", "Key Binding Pointer: 0x%p\n", dwKeybindingPointer);

	g_pKeyBinding = (kblist_t*)dwKeybindingPointer;

	while (g_pKeyBinding)
	{
		Utility->Log("KeyBinding.txt", " [KeyBinding][0x%p] %s = 0x%p\n", g_pKeyBinding, g_pKeyBinding->Name, g_pKeyBinding->Key);
		g_pKeyBinding = g_pKeyBinding->Next;
	}

	g_pKeyBinding = (kblist_t*)dwKeybindingPointer;
}

void UnhookKeyBindings()
{
	
}
// ===================================================================================