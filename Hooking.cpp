// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Hooking helper
void Hook::Add(DWORD Pointer, LPVOID FunctionToHook)
{
	hookinfo_t tmp;
	tmp.Pointer = Pointer;
	tmp.OriginalFunction = *(PDWORD)Pointer;
	tmp.HookedFunction = FunctionToHook;
	HookStorage.push_back(tmp);
}

void Hook::Apply()
{
	for (int i = 0; i < (int)HookStorage.size(); ++i)
		*(PDWORD)HookStorage[i].Pointer = (DWORD)HookStorage[i].HookedFunction;
}

void Hook::Remove()
{
	for (int i = 0; i < (int)HookStorage.size(); ++i)
		*(PDWORD)HookStorage[i].Pointer = HookStorage[i].OriginalFunction;
}
// ===================================================================================