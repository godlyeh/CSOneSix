// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Player infos
LocalPlayer g_Local;
PlayerInfo g_Player[MAX_CLIENTS + 1];
int *g_piEntityCount = NULL;
// ===================================================================================


// ===================================================================================
// Player info updates, etc..
void PlayerInfo::UpdateInfo()
{
	hud_player_info_t PlayerInfo;
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(Index);
	g_oEngine.pfnGetPlayerInfo(Index, &PlayerInfo);

	// Info
	if (strlen(Name) > 0)
		strcpy_s(Name, PlayerInfo.name);
	Alive = pEntity->curstate.solid == 3;
	Valid = EngineHelper::ValidPlayer(Index);

	// Position
	VectorCopy(pEntity->origin, Origin);
	VectorCopy(pEntity->angles, Angles);
}

void LocalPlayer::Reset()
{
	RoundsPlayed = 0;
	LevelName[0] = '\0';
}

void LocalPlayer::Update()
{
	if (EngineHelper::IsConnected())
	{
		EntityCount = *g_piEntityCount;
		Index = g_oEngine.GetLocalPlayer()->index;
		if (_stricmp(LevelName, g_oEngine.pfnGetLevelName()))
			strcpy_s(LevelName, g_oEngine.pfnGetLevelName());

		UpdateInfo();
	}
}

void InitializePlayerInfos()
{
	g_Local.Reset();
	g_piEntityCount = (int*)Utility->FindPattern("hw.dll", "3B 05 ? ? ? ? 7D 17 8D 04 40");

	for (int i = 0; i <= MAX_CLIENTS; ++i)
		g_Player[i].Index = i;

	Utility->DeleteLog("EntityInfo.txt");
	Utility->Log("EntityInfo.txt", "Max Entity: 0x%p (%i)", g_piEntityCount, *g_piEntityCount);
}
// ===================================================================================