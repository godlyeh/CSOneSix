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
void LocalPlayer::Reset()
{
	RoundsPlayed = 0;
	LevelName[0] = '\0';
}

void LocalPlayer::Update()
{
	if (EngineHelper::IsConnected())
	{
		Index = g_oEngine.GetLocalPlayer()->index;
		if (_stricmp(LevelName, g_oEngine.pfnGetLevelName()))
			strcpy_s(LevelName, g_oEngine.pfnGetLevelName());
	}
}

void InitializePlayerInfos()
{
	g_Local.Reset();

	for (int i = 0; i < MAX_CLIENTS; ++i)
		g_Player[i].Index = i;
}
// ===================================================================================