#include "Main.h"

CMovement* g_pMovement = new CMovement();

void CMovement::Fix(usercmd_t*pCmd, float*Out)
{
	Vector vecViewForward, vecViewRight, vecViewUp;
	EngineHelper::AngleVectors(Out, vecViewForward, vecViewRight, vecViewUp);

	Vector vecModForward, vecModRight, vecModUp;
	EngineHelper::AngleVectors(pCmd->viewangles, vecModForward, vecModRight, vecModUp);

	vecViewForward.Normalize();
	vecViewRight.Normalize();
	vecViewUp.Normalize();

	Vector vecMoveFix[3] =
	{
		Vector(pCmd->forwardmove * vecViewForward),
		Vector(pCmd->sidemove * vecViewRight),
		Vector(pCmd->upmove * vecViewUp),
	};
	pCmd->forwardmove =
		DotProduct(vecMoveFix[0], vecModForward) +
		DotProduct(vecMoveFix[1], vecModForward) +
		DotProduct(vecMoveFix[2], vecModForward);
	pCmd->sidemove =
		DotProduct(vecMoveFix[0], vecModRight) +
		DotProduct(vecMoveFix[1], vecModRight) +
		DotProduct(vecMoveFix[2], vecModRight);
	pCmd->upmove =
		DotProduct(vecMoveFix[0], vecModUp) +
		DotProduct(vecMoveFix[1], vecModUp) +
		DotProduct(vecMoveFix[2], vecModUp);
}