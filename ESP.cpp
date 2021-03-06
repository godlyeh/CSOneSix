// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// ESP handler
color_t ESP::GetTeamColor(int PlayerID)
{
	if (g_Local.Team == NULL)
		return rgb(128, 128, 128);

	if (g_Player[PlayerID].Team != NULL)
	{
		if (g_Player[PlayerID].Team->TeamNumber == 1) // Terrorist
		{
			if (g_Player[PlayerID].Visible)
				return rgb(255, 0, 128);
			return rgb(255, 0, 0);
		}

		if (g_Player[PlayerID].Team->TeamNumber == 2) // CT
		{
			if (g_Player[PlayerID].Visible)
				return rgb(0, 128, 255);
			return rgb(0, 0, 255);
		}
	}
	return rgb(128, 128, 128);
}

bool ESP::IsWeapon(int EntityID)
{
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(EntityID);
	if (pEntity && (strstr(pEntity->model->name, "models/w_") || strstr(pEntity->model->name, "models/p_")))
		return true;

	return false;
}

std::string ESP::GetSequenceString(int PlayerID)
{
	int Sequence = Cstrike_SequenceInfo[g_Player[PlayerID].Sequence];
	int GaitSequence = g_Player[PlayerID].GaitSequence;
	static std::string strRet; strRet.clear();

	if (GaitSequence == GAITSEQUENCE_STAND)			strRet = "[STANDING";
	if (GaitSequence == GAITSEQUENCE_DUCK)			strRet = "[DUCKING";
	if (GaitSequence == GAITSEQUENCE_WALK)			strRet = "[WALKING";
	if (GaitSequence == GAITSEQUENCE_RUNNING)		strRet = "[RUNNING";
	if (GaitSequence == GAITSEQUENCE_DUCKMOVE)		strRet = "[DUCKMOVING";
	if (GaitSequence == GAITSEQUENCE_JUMP)			strRet = "[JUMPING";

	if (Sequence &eSequence::SEQUENCE_SHOOT)		strRet += " + SHOOTING";
	if (Sequence &eSequence::SEQUENCE_RELOAD)		strRet += " + RELOADING";
	if (Sequence &eSequence::SEQUENCE_THROW)		strRet += " + THROWING";
	if (Sequence &eSequence::SEQUENCE_ARM_C4)		strRet += " + ARMING C4";
	if (Sequence &eSequence::SEQUENCE_SHIELD)		strRet += " + SHIELDED";

	return strRet + "]";
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

	// YSTEP, automatically place text
#define YSTEP vScreen[1] -= (Draw::GetStringHeight() + 2);
	YSTEP;
	
	// Weapon
	if (Variable::WeaponName)
	{
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), Player->Weapon);
		YSTEP;
	}

	// Name
	if (Variable::Name && Player->Name != NULL)
	{
		Draw::DrawString(true, true, vScreen, Color, Player->Name);
		YSTEP;
	}

	// Sequence
	if (Variable::Sequence)
	{
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 255), "%s", GetSequenceString(PlayerID).c_str());
		YSTEP;
	}

	// Distance
	if (Variable::Distance)
	{
		Draw::DrawString(true, true, vScreen, Color, "%.0fm", VectorDistance(g_Local.Origin, Player->Origin) / 22.0f);
		YSTEP;
	}

	// Box
	if (Variable::Box)
	{
		Draw::Draw3DBox(PlayerID, 2, Color);
	}

	// Aim Draw
	if (Variable::AimDrawPosition)
	{
		Aimbot::GetAimVector(PlayerID, vOrigin);
		if (EngineHelper::WorldToScreen(vOrigin, vScreen))
			Draw::FillRGBA((int)vScreen.x - 1, (int)vScreen.y - 1, 3, 3, rgb(128, 0, 0));
	}

	// Aim Target
	if (Variable::AimDrawTarget && PlayerID == Aimbot::AimTarget)
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 255), "AIM TARGET");
}

void ESP::DrawWeapon(int EntityID)
{
	EntityInfo* Entity = &g_Entity[EntityID];

	if (Entity->Valid == false)
		return;

	if (IsWeapon(EntityID) == false)
		return;

	Vector vScreen, vOrigin = Entity->Origin;
	vOrigin.z += Variable::GroundHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// YSTEP, automatically place text
#define YSTEP vScreen[1] -= (Draw::GetStringHeight() + 2);
	YSTEP;

	// Weapon names on ground
	if (Variable::WeaponGroundName && strlen(Entity->Weapon) > 0)
	{
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), Entity->Weapon);
		YSTEP;
	}

	// Distance
	if (Variable::DistanceGround)
	{
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "%.0fm", VectorDistance(g_Local.Origin, Entity->Origin) / 22.0f);
		YSTEP;
	}
}

void ESP::DrawEntity(int EntityID)
{
	EntityInfo* Entity = &g_Entity[EntityID];

	if (Entity->Valid == false)
		return;

	if (IsWeapon(EntityID))
		return;

	Vector vScreen, vOrigin = Entity->Origin;
	vOrigin.z += Variable::EntityHeightCorrection;

	// Check entity is in screen and get coordinates
	if (EngineHelper::WorldToScreen(vOrigin, vScreen) == false)
		return;

	// YSTEP, automatically place text
#define YSTEP vScreen[1] -= (Draw::GetStringHeight() + 2);
	YSTEP;

	// Hostage
	if (Variable::Hostage && Entity->IsHostage)
	{
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "Hostage");
		YSTEP;
	}

	// Distance
	if (Variable::DistanceEntity)
	{
		Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), "%.0fm", VectorDistance(g_Local.Origin, Entity->Origin) / 22.0f);
		YSTEP;
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