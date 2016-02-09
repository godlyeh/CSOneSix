#pragma once

class CMovement
{
public:
	void Fix(usercmd_t*pCmd, float*Out);
};

extern CMovement* g_pMovement;