// ===================================================================================
// Aimbot handler
#define AIMTEAM_ENEMY 0
#define AIMTEAM_FRIENDLY 1
#define AIMTEAM_BOTH 2

#define INVALID_TARGET -1

namespace Aimbot
{
	// Variables
	static bool Active = false;
	static int AimTarget = -1;
	static Vector AimAngles;

	// Funcs
	void GetAimVector(int PlayerID, float* Out);
	bool ValidTeam(int PlayerID);
	bool ValidAimTarget(int PlayerID);
	int FindTarget();
	bool IsAimkeyPressed();
	void PredictVelocityViewangles(float* ViewAngles, float* Velocity, float* Out);
	void CL_CreateMove(usercmd_t* pCmd);
}
// ===================================================================================