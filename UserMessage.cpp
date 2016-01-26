// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
usermsg_t* g_pUserMsg;

pfnUserMsgHook oResetHUD = NULL;
// ===================================================================================


// ===================================================================================
// UserMsg
void ResetHUD(const char *pszName, int iSize, void *pbuf)
{
	AtRoundStart();
	oResetHUD(pszName, iSize, pbuf);
}
// ===================================================================================


// ===================================================================================
// UserMsg list hook
void HookUserMsgList()
{
	DWORD dwUserMsgPointer = Utility->FindPattern("hw.dll", "8B 35 ? ? ? ? 83 C4 30 85 F6");
	dwUserMsgPointer = *(PDWORD)dwUserMsgPointer;

	Utility->DeleteLog("UserMsg.txt");
	Utility->Log("UserMsg.txt", "UserMsg List Pointer: 0x%p (Module: 0x%p)\n", dwUserMsgPointer, Utility->CalcModuleOffset(dwUserMsgPointer));

	g_pUserMsg = (usermsg_t*)dwUserMsgPointer;

	while (g_pUserMsg)
	{
		Utility->Log("UserMsg.txt", " [UserMsgList][0x%p] %s = 0x%p (Module: 0x%p)\n", g_pUserMsg, g_pUserMsg->Name, g_pUserMsg->Function, Utility->CalcModuleOffset((DWORD)g_pUserMsg));

#define HookUserMsg(name) { if (!_stricmp(g_pUserMsg->Name, #name)) { \
								o##name = (pfnUserMsgHook)g_pUserMsg->Function; \
								/*g_pUserMsg->Function = ##name;*/HOOK(&g_pUserMsg->Function, ##name); } }
		
		HookUserMsg(ResetHUD);

		g_pUserMsg = g_pUserMsg->Next;
	}

	g_pUserMsg = (usermsg_t*)dwUserMsgPointer;
}
// ===================================================================================