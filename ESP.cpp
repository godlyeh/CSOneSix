// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// ESP handler
color_t ESP::GetTeamColor(int PlayerID)
{
	if (g_Player[PlayerID].Team != NULL)
	{
		if (g_Player[PlayerID].Team->TeamNumber == 1) // Terrorist
		{
			return rgb(255, 0, 0);
		}

		if (g_Player[PlayerID].Team->TeamNumber == 2) // CT
		{
			return rgb(0, 0, 255);
		}
	}
	return rgb(128, 128, 128);
}

void ESP::DrawPlayer(int PlayerID)
{
	EntityInfo* Player = &g_Player[PlayerID];

	if (Player->Valid == false)
		return;

	// Get infos
	color_t Color = GetTeamColor(PlayerID);
	Vector vScreen, vOrigin = Player->Origin;
	vOrigin.z += Variable::PlayerHeightCorrection;
	vOrigin.z += Player->Maxs.z;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

#define YSTEP vScreen[1] -= (Draw::GetStringHeight() + 2);
	YSTEP;

	// Weapon
	if (Variable::WeaponName)
	{
		Draw::DrawString(true, true, vScreen, Color, Player->Weapon);
		YSTEP;
	}

	// Name
	if (Variable::Name && Player->Name != NULL)
	{
		Draw::DrawString(true, true, vScreen, Color, Player->Name);
		YSTEP;
	}

	// Distance
	if (Variable::Distance)
	{
		Draw::DrawString(true, true, vScreen, Color, "%.0fm", VectorDistance(g_Local.Origin, Player->Origin) / 22.0f);
		YSTEP;
	}
}

void ESP::DrawWeapon(int EntityID)
{
	EntityInfo* Entity = &g_Entity[EntityID];

	if (Entity->Valid == false)
		return;

	Vector vScreen, vOrigin = Entity->Origin;
	vOrigin.z += Variable::GroundHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// Weapon names on ground
	if (Variable::WeaponGroundName && strlen(Entity->Weapon) > 0)
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "%s", Entity->Weapon);
}

void ESP::DrawEntity(int EntityID)
{
	EntityInfo* Entity = &g_Entity[EntityID];

	if (Entity->Valid == false)
		return;

	Vector vScreen, vOrigin = Entity->Origin;
	vOrigin.z += Variable::EntityHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// Hostage
	if (Variable::Hostage && Entity->IsHostage)
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "Hostage");
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