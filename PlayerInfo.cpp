// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Player infos
LocalPlayer g_Local;
PlayerInfo g_Player[MAX_CLIENTS];
// ===================================================================================


// ===================================================================================
// Player info updates, etc..
DWORD dwMaxPlayerInfoPtr = 0;

void LocalPlayer::Reset()
{
	RoundsPlayed = 0;
	LevelName[0] = '\0';
}

void LocalPlayer::Update()
{
	if (EngineHelper::IsConnected())
	{
		MaxEntity = *(PINT)dwMaxPlayerInfoPtr;
		Index = g_oEngine.GetLocalPlayer()->index;
		if (_stricmp(LevelName, g_oEngine.pfnGetLevelName()))
			strcpy_s(LevelName, g_oEngine.pfnGetLevelName());
	}
}

void InitializePlayerInfos()
{
	g_Local.Reset();
	dwMaxPlayerInfoPtr = Utility->FindPattern("hw.dll", "3B 05 ? ? ? ? 7D 17 8D 04 40");

	for (int i = 0; i <= MAX_CLIENTS; ++i)
		g_Player[i].Index = i;

	Utility->DeleteLog("EntityInfo.txt");
	Utility->Log("EntityInfo.txt", "Max Entity: 0x%p (%i)", dwMaxPlayerInfoPtr, *(PINT)dwMaxPlayerInfoPtr);
}
// ===================================================================================