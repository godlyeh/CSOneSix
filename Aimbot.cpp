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
	StudioHelper::GetPlayerBone(PlayerID, 0, iBone, vOrigin);
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
// ===================================================================================