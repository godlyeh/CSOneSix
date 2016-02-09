// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================

// ===================================================================================
// Aimbot handler
void Aimbot::GetAimVector(int PlayerID, float* Out)
{
	int iBone = 7;
	if (Variable::AimPosition == 2) iBone = 5;
	if (Variable::AimPosition == 3) iBone = 2;
	Vector vF, vR, vU, vOrigin;
	StudioHelper::GetPlayerBone(PlayerID, iBone, vOrigin);
	if (g_Player[PlayerID].Ducking)
		vOrigin.z += 2;

	if (Variable::AimPosition == 0 || Variable::AimPosition == 1)
	{
		EngineHelper::AngleVectors(Vector(g_Player[PlayerID].Angles.x, g_Player[PlayerID].Angles.y, 0.0f), vF, vR, vU);
		if (Variable::AimPosition == 0) vOrigin = vOrigin + vF + vR + vU * 5;
		if (Variable::AimPosition == 1) vOrigin = vOrigin + vF + vR + vU;
	}

	VectorCopy(vOrigin, Out);
}

bool Aimbot::ValidTeam(int PlayerID)
{
	if (g_Local.Team == NULL)
		return false;

	if (Variable::AimTeam == AIMTEAM_BOTH)
		return true;

	if (Variable::AimTeam == AIMTEAM_ENEMY && g_Local.Team->TeamNumber != g_Player[PlayerID].Team->TeamNumber)
		return true;

	if (Variable::AimTeam == AIMTEAM_FRIENDLY && g_Local.Team->TeamNumber == g_Player[PlayerID].Team->TeamNumber)
		return true;

	return false;
}

bool Aimbot::ValidAimTarget(int PlayerID)
{
	// Validity
	if (EngineHelper::ValidPlayer(PlayerID) == false)
		return false;

	if (ValidTeam(PlayerID) == false)
		return false;

	// Visible check, we could use Visible from entity storage as it uses all bones
	if (g_Player[PlayerID].AimOriginVisible == false)
		return false;

	return true;
}

int Aimbot::FindTarget() // This is the aim filter, here we pick the best possible aim target avaible
{
	// Invalidate target
	int iTarget = INVALID_TARGET;
	float flClosestTarget = 99999999.0f;

	// Loop players and get best target
	for (int i = 0; i <= MAX_CLIENTS; ++i)
	{
		// Valid
		if (ValidAimTarget(i) == false)
			continue;

		// Go by distance
		float flDistance = VectorDistance(g_Local.EyePosition, g_Player[i].AimOrigin);
		if (flDistance < flClosestTarget)
		{
			iTarget = i;
			flClosestTarget = flDistance;
		}
	}

	return iTarget;
}

bool Aimbot::IsAimkeyPressed()
{
	if (Variable::AimKey == 0)
		return true;

	int Aimkey = Variable::AimKey;
	if (Aimkey > 2) ++Aimkey;

	if (GetAsyncKeyState(Aimkey))
		return true;

	return false;
}

void Aimbot::PredictVelocityViewangles(float* ViewAngles, float* Velocity, float* Out)
{

}

void Aimbot::CL_CreateMove(usercmd_t* pCmd)
{
	Active = false;

	// Check aimbot
	if (Variable::Aimbot == 0 || IsAimkeyPressed() == false)
		return;

	// If weapon isnt ready, do nothing
	if (WeaponInfo::IsWeaponReady() == false)
		return;

	// If aimlock is enabled and aimtarget is still valid, skip findtarget and go directly to aiming
	if (Variable::AimLock && ValidAimTarget(AimTarget)) 
		goto AimLock;

	// Find best aim target
	AimTarget = FindTarget();

	if (AimTarget != INVALID_TARGET)
	{
	AimLock:

		// Aim at target
		EngineHelper::VectorToViewangles(g_Player[AimTarget].AimOrigin, AimAngles);
		VectorCopy(AimAngles, pCmd->viewangles);
		//g_oEngine.SetViewAngles(vAimAngles);
		
		// Autoshoot
		if (Variable::AimAutoshoot && !(pCmd->buttons &IN_ATTACK) && !(pCmd->buttons &IN_ATTACK2) && !(pCmd->buttons &IN_RELOAD))
			pCmd->buttons |= IN_ATTACK;

		Active = true;
	}

}
// ===================================================================================