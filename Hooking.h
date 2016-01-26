// ===================================================================================
// Hooking info
typedef struct
{
	DWORD Pointer;
	DWORD OriginalFunction;
	LPVOID HookedFunction;
}hookinfo_t;
// ===================================================================================


// ===================================================================================
// Hooking helper
#define HOOK(ptr, func) { Hook::Add((DWORD)ptr, (LPVOID)func); }

namespace Hook
{
	// Funcs
	void Add(DWORD Pointer, LPVOID FunctionToHook);
	void Apply();
	void Remove();

	// Array
	static std::vector<hookinfo_t> HookStorage;
}
// ===================================================================================