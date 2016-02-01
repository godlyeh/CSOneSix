// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// ESP handler
color_t ESP::GetTeamColor(int PlayerID)
{
	return rgb(128, 128, 128);
}

void ESP::DrawPlayer(int PlayerID)
{
	if (EngineHelper::ValidPlayer(PlayerID) == false)
		return;

	// Get infos
	color_t Color = GetTeamColor(PlayerID);
	Vector vScreen, vOrigin = g_Player[PlayerID].Origin;
	vOrigin.z += Variable::PlayerHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// Name
	if (Variable::Name)
		Draw::DrawString(true, true, vScreen, Color, g_Player[PlayerID].Name);
}

void ESP::DrawWeapon(int EntityID)
{
	if (EngineHelper::ValidEntity(EntityID) == false)
		return;

	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(EntityID);
	Vector vScreen, vOrigin = pEntity->origin;
	vOrigin.z += Variable::GroundHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// Weapon names on ground
	if (Variable::WeaponGroundName)
	{
		if (pEntity->model->name && strstr(pEntity->model->name, "models/w_"))
		{
			char szWeapon[64];
			strcpy_s(szWeapon, pEntity->model->name);
			*(strrchr(szWeapon, '.')) = 0;
			Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "%s", strrchr(szWeapon, '/') + 3);
		}
	}
}

void ESP::DrawEntity(int EntityID)
{
	if (EngineHelper::ValidEntity(EntityID) == false)
		return;

	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(EntityID);
	Vector vScreen, vOrigin = pEntity->origin;
	vOrigin.z += Variable::EntityHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// Hostage
	if (Variable::Hostage)
	{
		if (pEntity->model->name && strstr(pEntity->model->name, "models/hostage") && pEntity->curstate.solid == 3)
		{
			char szHostage[64];
			strcpy_s(szHostage, pEntity->model->name);
			*(strrchr(szHostage, '.')) = 0;
			Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "%s", strrchr(szHostage, '/') + 1);
		}
	}
}

void ESP::DrawESP()
{
	if (g_Local.EntityCount <= 0)
		return;

	// Loop through players and draw
	for (int i = 0; i <= MAX_CLIENTS; ++i)
		DrawPlayer(i);

	// Loop through entities and draw
	for (int i = MAX_CLIENTS; i < g_Local.EntityCount; ++i)
	{
		DrawWeapon(i);
		DrawEntity(i);
	}
}
// ===================================================================================