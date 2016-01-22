// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Sound
bool SkipSound = false;

void S_StartDynamicSound(int entnum, int entchannel, char* sample, float* origin, float volume, float attenuation, int timeofs, int pitch)
{
	SkipSound = false;
	Utility->Log("Sound.txt", " #%i %s\n", entnum, sample);

	// Do codenz here SkipSound = true to avoid playing sound
	if (entnum == 1 && strstr(sample, "player"))
		SkipSound = true;
}
// ===================================================================================


// ===================================================================================
// Studio table hook
CONTEXT GameCTX;
HANDLE hExceptionHandler;
DWORD dwSoundFunction = 0;
DWORD dwSoundRetAddr = 0;

__declspec(naked)void SoundGate()
{
	__asm
	{
		push ebp
		jmp dwSoundRetAddr
	}
}

LONG WINAPI SoundExceptionHandler(PEXCEPTION_POINTERS Exception)
{
	if (Exception->ContextRecord->Eip == dwSoundFunction)
	{
		dwSoundRetAddr = dwSoundFunction + 0x1;

		S_StartDynamicSound((int)(*(PDWORD)(Exception->ContextRecord->Esp + 0x4)),
			(int)(*(PDWORD)(Exception->ContextRecord->Esp + 0x8)),
			(char*)(*(DWORD*)(Exception->ContextRecord->Esp + 0xC)),
			(float*)(*(DWORD*)(Exception->ContextRecord->Esp + 0x10)),
			(float)(*(DWORD*)(Exception->ContextRecord->Esp + 0x14)),
			(float)(*(DWORD*)(Exception->ContextRecord->Esp + 0x18)),
			(int)(*(DWORD*)(Exception->ContextRecord->Esp + 0x1C)),
			(int)(*(DWORD*)(Exception->ContextRecord->Esp + 0x20)));

		Exception->ContextRecord->Eip = (DWORD)SoundGate;
		if (SkipSound)
			Exception->ContextRecord->Eip = *(PDWORD)Exception->ContextRecord->Esp + 0x3; // skip mov esp, 20

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

void HookSound()
{
	dwSoundFunction = Utility->FindPattern("hw.dll", "55 8B EC 83 EC 48 A1 ? ? ? ? 53", false);
	dwSoundRetAddr = dwSoundFunction + 0x1;

	Utility->DeleteLog("Sound.txt");
	Utility->Log("Sound.txt", "Sound Pointer: 0x%p (Module: 0x%p)\n", dwSoundFunction, Utility->CalcModuleOffset(dwSoundFunction));

	hExceptionHandler = AddVectoredExceptionHandler(TRUE, SoundExceptionHandler);

	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, Utility->GetProcessThread()->th32ThreadID);
	GetThreadContext(hThread, &GameCTX);

	CONTEXT ctx; ZeroMemory(&ctx, sizeof(CONTEXT));
	ctx = { CONTEXT_DEBUG_REGISTERS };
	ctx.Dr0 = dwSoundFunction;
	ctx.Dr7 = 1;

	SuspendThread(hThread);
	SetThreadContext(hThread, &ctx);
	ResumeThread(hThread);

	CloseHandle(hThread);
}

void UnhookSound()
{
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, Utility->GetProcessThread()->th32ThreadID);

	SuspendThread(hThread);
	SetThreadContext(hThread, &GameCTX);
	ResumeThread(hThread);

	CloseHandle(hThread);

	RemoveVectoredExceptionHandler(hExceptionHandler);
}
// ===================================================================================