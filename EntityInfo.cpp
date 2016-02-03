// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Player infos
LocalPlayer g_Local;
EntityInfo g_Player[MAX_CLIENTS + 1];
EntityInfo g_Entity[4096];
int *g_piEntityCount = NULL;
// ===================================================================================


// ===================================================================================
// Player info updates, etc..
char* EntityInfo::GetPlayerName()
{
	if (!dwGetPlayerName)
	{
		dwGetPlayerName = Utility->FindPattern("hw.dll", "05 ? ? ? ? 89 01 8B 45 08") - 0x250;
		Utility->Log("EntityInfo.txt", "Player Names: 0x%p\n", dwGetPlayerName);
	}
	else
		return (char*)(dwGetPlayerName + Index * 0x250);

	return NULL;
}

char* EntityInfo::GetPlayerWeaponName(char* WeaponName)
{
	*(strrchr(WeaponName, '.')) = 0;

	if (strstr(WeaponName, "shield"))
		return Utility->StringA("shield + %s", strrchr(WeaponName, '/') + 3 + 7);

	return strrchr(WeaponName, '/') + 3;
}

char* EntityInfo::GetWeaponName(char* WeaponName)
{
	*(strrchr(WeaponName, '.')) = 0;
	return strrchr(WeaponName, '/') + 3;
}

teaminfo_t* EntityInfo::GetPlayerTeam()
{
	if (!dwGetPlayerTeam)
	{
		dwGetPlayerTeam = Utility->FindPattern("client.dll", "8D 3C C5 ? ? ? ? E8 ? ? ? ? 50") + 0x4A - sizeof(teaminfo_t);
		Utility->Log("EntityInfo.txt", "Player Teams: 0x%p\n", dwGetPlayerTeam);
	}
	else
		return (teaminfo_t*)(dwGetPlayerTeam + Index * sizeof(teaminfo_t));

	return NULL;
}

void EntityInfo::UpdateInfo()
{
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(Index);
	if (!pEntity) return;

	// Info
	Alive = pEntity->curstate.solid == 3;

	// Entity info
	IsHostage = false;
	if (pEntity->model && Alive && pEntity->model->name && strstr(pEntity->model->name, "models/hostage"))
		IsHostage = true;

	// Player specific
	if (Index >= 0 && Index <= MAX_CLIENTS)
	{
		// Info
		Valid = EngineHelper::ValidPlayer(Index);
		Sequence = pEntity->curstate.sequence;
		GaitSequence = pEntity->curstate.gaitsequence;
		Team = GetPlayerTeam();
		if (GetPlayerName() != NULL)
			strcpy_s(Name, GetPlayerName());

		// Weapon
		model_t* WeaponModel = g_oStudio.GetModelByIndex(pEntity->curstate.weaponmodel);
		if (WeaponModel && WeaponModel->name && (strstr(WeaponModel->name, "models/p_") || strstr(WeaponModel->name, "models/shield/p_")))
		{
			strcpy_s(Weapon, WeaponModel->name);
			strcpy_s(Weapon, GetPlayerWeaponName(Weapon));
		}
	}
	else
	{
		// Info
		Valid = EngineHelper::ValidEntity(Index);

		// Weapon
		if (pEntity->model && pEntity->model->name && strstr(pEntity->model->name, "models/w_"))
		{
			strcpy_s(Weapon, pEntity->model->name);
			strcpy_s(Weapon, GetWeaponName(Weapon));
		}
	}

	// Position
	VectorCopy(pEntity->origin, Origin);
	VectorCopy(pEntity->angles, Angles);
	VectorCopy(pEntity->curstate.mins, Mins);
	VectorCopy(pEntity->curstate.maxs, Maxs);
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
	for (int i = 0; i < 4096; ++i)
		g_Entity[i].Index = i;

	Utility->DeleteLog("EntityInfo.txt");
	Utility->Log("EntityInfo.txt", "Max Entity: 0x%p (%i)\n", g_piEntityCount, *g_piEntityCount);
}
// ===================================================================================