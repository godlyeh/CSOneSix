// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// WeaponInfo functions
weapon_t* WeaponInfo::GetWeaponByID(int WeaponID)
{
	//GetWEAPONByID to get weapon info
	if (dwGetWeaponByID == NULL)
		return NULL;

	return ((weapon_t*(__cdecl*)(int WeaponID))dwGetWeaponByID)(WeaponID);
}

bool WeaponInfo::IsWeaponReady()
{
	// Check if weapon is ready (ptrs etc retrieved)
	weapon_t* pWeapon = WeaponInfo::GetWeaponByID(g_Local.WeaponID);
	if (pWeapon == NULL)
		return false;

	if (pWeapon->Ammo == 0)
		return false;

	if (pWeapon->Reloading)
		return false;

	return true;
}

eWeaponType WeaponInfo::GetWeaponType(int WeaponID)
{
	// Simplifies things when doing nospread, aimbot etc. anything that required to lock out weapons
	eWeaponType WeaponType = WEAPONTYPE_NONE;
	if (WeaponID == WEAPON_P228 || WeaponID == WEAPON_USP || WeaponID == WEAPON_GLOCK18 || WeaponID == WEAPON_DEAGLE || WeaponID == WEAPON_ELITE || WeaponID == WEAPON_FIVESEVEN)
		WeaponType = WEAPONTYPE_PISTOL;
	if (WeaponID == WEAPON_M3 || WeaponID == WEAPON_XM1014)
		WeaponType = WEAPONTYPE_SHOTGUN;
	if (WeaponID == WEAPON_MAC10 || WeaponID == WEAPON_UMP45 || WeaponID == WEAPON_MP5 || WeaponID == WEAPON_TMP || WeaponID == WEAPON_P90)
		WeaponType = WEAPONTYPE_SMG;
	if (WeaponID == WEAPON_AUG || WeaponID == WEAPON_GALIL || WeaponID == WEAPON_FAMAS || WeaponID == WEAPON_M4A1 || WeaponID == WEAPON_AK47 || WeaponID == WEAPON_SG552 || WeaponID == WEAPON_M249)
		WeaponType = WEAPONTYPE_RIFLE;
	if (WeaponID == WEAPON_SCOUT || WeaponID == WEAPON_G3SG1 || WeaponID == WEAPON_SG550 || WeaponID == WEAPON_AWP)
		WeaponType = WEAPONTYPE_SNIPER;
	if (WeaponID == WEAPON_NONE || WeaponID == WEAPON_UNKNOWN1 || WeaponID == WEAPON_HEGRENADE || WeaponID == WEAPON_C4 || WeaponID == WEAPON_SMOKEGRENADE || WeaponID == WEAPON_FLASHBANG)
		WeaponType = WEAPONTYPE_MISC;
	if (WeaponID == WEAPON_KNIFE)
		WeaponType = WEAPONTYPE_KNIFE;

	return WeaponType;
}

void WeaponInfo::Init()
{
	// GetWEAPONByID is the name in dylib
	dwGetWeaponByID = Utility->FindPattern("client.dll", "8B 44 24 04 48 83 F8 1D 0F 87 ? ? ? ?", false);

	Utility->DeleteLog("Weapon.txt");
	Utility->Log("Weapon.txt", "GetWeaponByID: 0x%p\n", dwGetWeaponByID);
}
// ===================================================================================


// ===================================================================================
// Spread and recoil handling
float WeaponInfo::GetSpreadFactor()
{
	// Retrieve weapon info
	weapon_t* pWeapon = GetWeaponByID(g_Local.WeaponID);
	int WeaponID = pWeapon->WeaponID;
	eWeaponBit WeaponBit = pWeapon->WeaponBit;
	bool OnGround = (g_Local.Flags &FL_ONGROUND) != 0;
	bool Ducking = (g_Local.Flags &FL_DUCKING) != 0;
	float FOV = g_Local.FOV;
	float Speed = g_Local.Velocity.Length2D();
	float SpreadVar = pWeapon->SpreadVar;
	float Recoil = (float)pWeapon->Recoil;
	float SpreadFactor = pWeapon->SpreadVar;
	
	// Factor spread based by weapon
	if (WeaponID == WEAPON_P228) // 1
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = pWeapon->SpreadVar - (0.325f - (g_pGlobals->time - pWeapon->PredRecoil)) * 0.3f;
			if (SpreadVar < 0.6f) SpreadVar = 0.6f;
			if (SpreadVar > 0.9f) SpreadVar = 0.9f;
		}

		// Factor spread
		if (OnGround)
		{
			if (Speed > 0.0f)
				SpreadFactor = (1.0f - SpreadVar) * 0.255f;
			else if (Ducking == true)
				SpreadFactor = (1.0f - SpreadVar) * 0.075f;
			else
				SpreadFactor = (1.0f - SpreadVar) * 0.15f;
		}
		else
			SpreadFactor = (1.0f - SpreadVar) * 1.5f;
	}

	if (WeaponID == WEAPON_SCOUT) // 3
	{
		// Factor spread
		if (OnGround)
		{
			if (Speed <= 170.0f)
			{
				if (Ducking)
					SpreadFactor = 0.0f;
				else
					SpreadFactor = 0.007f;
			}
			else
				SpreadFactor = 0.075f;
		}
		else
			SpreadFactor = 0.2f;

		if (FOV == 90.0f)
			SpreadFactor += 0.025f;
	}
	
	if (WeaponID == WEAPON_MAC10) // 7
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 200) + 0.6f;
		SpreadVar = fminf(1.65f, Spread);

		// Factor spread
		if (OnGround)
			SpreadFactor = SpreadVar * 0.03f;
		else
			SpreadFactor = SpreadVar * 0.375f;
	}

	if (WeaponID == WEAPON_AUG) // 8
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 215) + 0.3f;
		SpreadVar = fminf(1.0f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140)
				SpreadFactor = SpreadVar * 0.02f;
			else
				SpreadFactor = SpreadVar * 0.07f + 0.035f;
		}
		else
			SpreadFactor = SpreadVar * 0.4f + 0.035f;
	}
	
	if (WeaponID == WEAPON_ELITE) // 10 - inaccurate, todo: center guns based on wich is firing
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = pWeapon->SpreadVar - (0.325f - (g_pGlobals->time - pWeapon->PredRecoil)) * 0.275f;
			if (SpreadVar < 0.55f) SpreadVar = 0.55f;
			if (SpreadVar > 0.88f) SpreadVar = 0.88f;
		}

		// Factor spread
		if (OnGround)
		{
			if (Speed > 0.0f)
				SpreadFactor = (1.0f - SpreadVar) * 0.175f;
			else if (Ducking == true)
				SpreadFactor = (1.0f - SpreadVar) * 0.08f;
			else
				SpreadFactor = (1.0f - SpreadVar) * 0.1f;
		}
		else
			SpreadFactor = (1.0f - SpreadVar) * 1.3f;
	}
	
	if (WeaponID == WEAPON_FIVESEVEN) // 11
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = pWeapon->SpreadVar - (0.275f - (g_pGlobals->time - pWeapon->PredRecoil)) * 0.25f;
			if (SpreadVar < 0.725f) SpreadVar = 0.725f;
			if (SpreadVar > 0.92f) SpreadVar = 0.92f;
		}

		// Factor spread
		if (OnGround)
		{
			if (Speed > 0)
				SpreadFactor = (1.0f - SpreadVar) * 0.255f;
			else if (Ducking == true)
				SpreadFactor = (1.0f - SpreadVar) * 0.075f;
			else
				SpreadFactor = (1.0f - SpreadVar) * 0.15f;
		}
		else
			SpreadFactor = (1.0f - SpreadVar) * 1.5f;
	}
	
	if (WeaponID == WEAPON_UMP45) // 12
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil / 210) + 0.5f;
		SpreadVar = fminf(1.0f, Spread);

		// Factor spread
		if (OnGround)
			SpreadFactor = SpreadVar * 0.04f;
		else
			SpreadFactor = SpreadVar * 0.24f;
	}

	if (WeaponID == WEAPON_SG550) // 13
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = (g_pGlobals->time - pWeapon->PredRecoil) * 0.35f + 0.65f;
			if (SpreadVar > 0.98f)
				SpreadVar = 0.98f;
		}

		// Factor spread
		if (OnGround)
		{
			if (Speed > 0.0f)
				SpreadFactor = (1.0f - SpreadVar) * 0.15f;
			else if (Ducking == true)
				SpreadFactor = (1.0f - SpreadVar) * 0.04f;
			else
				SpreadFactor = (1.0f - SpreadVar) * 0.05f;
		}
		else
			SpreadFactor = (1.0f - SpreadVar) * 0.45f;

		if (FOV == 90.0f)
			SpreadVar += 0.025f;
	}
	
	if (WeaponID == WEAPON_GALIL) // 14
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 200) + 0.35f;
		SpreadVar = fminf(1.25f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140.0f)
				SpreadFactor = SpreadVar * 0.0375f;
			else
				SpreadFactor = SpreadVar * 0.07f + 0.04f;
		}
		else
			SpreadFactor = SpreadVar * 0.3f + 0.04f;
	}

	if (WeaponID == WEAPON_FAMAS) // 15
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 215) + 0.3f;
		SpreadVar = fminf(1.0f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140.0f)
				SpreadFactor = SpreadVar * 0.02f;
			else
				SpreadFactor = SpreadVar * 0.07f + 0.03f;
		}
		else
			SpreadFactor = SpreadVar * 0.3f + 0.03f;

		if (WeaponBit != WEAPONBIT_FAMASBURST)
			SpreadFactor += 0.01f;

		if (WeaponBit == WEAPONBIT_FAMASBURST && pWeapon->BurstSpread != 0.0f)
			SpreadFactor += 0.05f;
	}

	if (WeaponID == WEAPON_USP) // 16
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = pWeapon->SpreadVar - (0.3f - (g_pGlobals->time - pWeapon->PredRecoil)) * 0.275f;
			if (SpreadVar < 0.6f) SpreadVar = 0.6f;
			if (SpreadVar > 0.92f) SpreadVar = 0.92f;
		}

		// Factor spread
		if (WeaponBit == WEAPONBIT_USPSILENCER)
		{
			if (OnGround)
			{
				if (Speed > 0.0f)
					SpreadFactor = (1.0f - SpreadVar) * 0.225f;
				else if (Ducking == true)
					SpreadFactor = (1.0f - SpreadVar) * 0.08f;
				else
					SpreadFactor = (1.0f - SpreadVar) * 0.1f;
			}
			else
				SpreadFactor = (1.0f - SpreadVar) * 1.2f;
		}
		else
		{
			if (OnGround)
			{
				if (Speed > 0.0f)
					SpreadFactor = (1.0f - SpreadVar) * 0.25f;
				else if (Ducking == true)
					SpreadFactor = (1.0f - SpreadVar) * 0.125f;
				else
					SpreadFactor = (1.0f - SpreadVar) * 0.15f;
			}
			else
				SpreadFactor = (1.0f - SpreadVar) * 1.3f;
		}
	}
	
	if (WeaponID == WEAPON_GLOCK18) // 17
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = pWeapon->SpreadVar - (0.325f - (g_pGlobals->time - pWeapon->PredRecoil)) * 0.275f;
			if (SpreadVar < 0.6f) SpreadVar = 0.6f;
			if (SpreadVar > 0.9f) SpreadVar = 0.9f;
		}

		// Factor Spread
		if (WeaponBit >= WEAPONBIT_GLOCKBURST)
		{
			if (OnGround)
			{
				if (Speed > 0.0f)
					SpreadFactor = (1.0f - SpreadVar) * 0.185f;
				else if (Ducking == true)
					SpreadFactor = (1.0f - SpreadVar) * 0.095f;
				else
					SpreadFactor = (1.0f - SpreadVar) * 0.3f;
			}
			else
				SpreadFactor = (1.0f - SpreadVar) * 1.2f;
		}
		else
		{
			if (OnGround)
			{
				if (Speed > 0.0f)
					SpreadFactor = (1.0f - SpreadVar) * 0.165f;
				else if (Ducking == true)
					SpreadFactor = (1.0f - SpreadVar) * 0.075f;
				else
					SpreadFactor = (1.0f - SpreadVar) * 0.1f;
			}
			else
				SpreadFactor = 1.0f - SpreadVar;
		}

		if (!WeaponBit)
			SpreadFactor -= 0.05f;
		else if (pWeapon->PistolBurstSpread != 0.0f)
			SpreadFactor += 0.1f;
		
	}

	if (WeaponID == WEAPON_AWP) // 18
	{
		// Factor spread
		if (OnGround)
		{
			if (Speed <= 10)
			{
				if (Ducking)
					SpreadFactor = 0.0f;
				else
					SpreadFactor = 0.001f;
			}
			else if (Speed <= 140)
				SpreadFactor = 0.1f;
			else
				SpreadFactor = 0.25f;
		}
		else
			SpreadFactor = 0.85f;

		if (FOV == 90.0f)
			SpreadFactor += 0.08f;
	}

	if (WeaponID == WEAPON_MP5) // 19
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil) * 0.004543389368468878f + 0.45f;
		SpreadVar = fminf(0.75f, Spread);

		// Factor spread
		if (OnGround)
			SpreadFactor = SpreadVar * 0.04f;
		else
			SpreadFactor = SpreadVar * 0.2f;
	}
	
	if (WeaponID == WEAPON_M249) // 20
	{
		// Calc spreadvar
		if (Recoil != 0.0f) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 175) + 0.4f;
		SpreadVar = fminf(0.9f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140.0f)
				SpreadFactor = SpreadVar * 0.03f;
			else
				SpreadFactor = SpreadVar * 0.095f + 0.045f;
		}
		else
			SpreadFactor = SpreadVar * 0.5f + 0.045f;
	}

	if (WeaponID == WEAPON_M4A1) // 22
	{
		// Calc spreadvar
		if (Recoil != 0.0f) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 220) + 0.3f;
		SpreadVar = fminf(1.0f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140.0f)
			{
				if (WeaponBit == WEAPONBIT_M4A1SILENCER)
					SpreadFactor = SpreadVar * 0.025f;
				else
					SpreadFactor = SpreadVar * 0.02f;
			}
			else
				SpreadFactor = SpreadVar * 0.07f + 0.035f;
		}
		else
			SpreadFactor = SpreadVar * 0.4f + 0.035f;
	}

	if (WeaponID == WEAPON_TMP) // 23
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 200) + 0.55f;
		SpreadVar = fminf(1.4f, Spread);

		// Factor spread
		if (OnGround)
			SpreadFactor = SpreadVar * 0.03f;
		else
			SpreadFactor = SpreadVar * 0.25f;
	}
	
	if (WeaponID == WEAPON_G3SG1) // 24
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil == 0.0f)
			SpreadVar = 0.98f;
		else
		{
			SpreadVar = (g_pGlobals->time - pWeapon->PredRecoil) * 0.3f + 0.55f;
			if (SpreadVar > 0.98f) SpreadVar = 0.98f;
		}

		// Factor spread
		if (OnGround)
		{
			if (Speed > 0.0f)
				SpreadFactor = (1.0f - SpreadVar) * 0.15f;
			else if (Ducking == true)
				SpreadFactor = (1.0f - SpreadVar) * 0.035f;
			else
				SpreadFactor = (1.0f - SpreadVar) * 0.055f;
		}
		else
			SpreadFactor = (1.0f - SpreadVar) * 0.45f;

		if (FOV == 90.0f)
			SpreadFactor += 0.025f;
	}

	if (WeaponID == WEAPON_DEAGLE) // 26 - inaccurate (did i forget something - punchangles done differently?)
	{
		// Calc spreadvar
		if (pWeapon->PredRecoil != 0.0f)
		{
			SpreadVar = pWeapon->SpreadVar - (0.4f - (g_pGlobals->time - pWeapon->PredRecoil)) * 0.35f;
			if (SpreadVar < 0.55f) SpreadVar = 0.55f;
			if (SpreadVar > 0.9f) SpreadVar = 0.9f;
		}

		// Factor spread
		if (OnGround)
		{
			if (Speed > 0.0f)
				SpreadFactor = (1.0f - SpreadVar) * 0.25f;
			else if (Ducking == true)
				SpreadFactor = (1.0f - SpreadVar) * 0.115f;
			else
				SpreadFactor = (1.0f - SpreadVar) * 0.13f;
		}
		else
			SpreadFactor = (1.0f - SpreadVar) * 1.5f;
	}

	if (WeaponID == WEAPON_SG552) // 27
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 220) + 0.3f;
		SpreadVar = fminf(1.0f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140.0f)
				SpreadFactor = SpreadVar * 0.02f;
			else
				SpreadFactor = SpreadVar * 0.075f + 0.035f;
		}
		else
			SpreadFactor = SpreadVar * 0.45f + 0.035f;
	}
	
	if (WeaponID == WEAPON_AK47) // 28
	{
		// Calculate spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil * Recoil / 200) + 0.35f;
		SpreadVar = fminf(1.25f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 140.0f)
				SpreadFactor = SpreadVar * 0.0275f;
			else
				SpreadFactor = SpreadVar * 0.07f + 0.04f;
		}
		else
			SpreadFactor = SpreadVar * 0.4f + 0.04f;
	}

	if (WeaponID == WEAPON_P90) // 30
	{
		// Calc spreadvar
		if (Recoil) Recoil -= 1;
		float Spread = (Recoil * Recoil / 175) + 0.45f;
		SpreadVar = fminf(1.0f, Spread);

		// Factor spread
		if (OnGround)
		{
			if (Speed <= 170.0f)
				SpreadFactor = SpreadVar * 0.045f;
			else
				SpreadFactor = SpreadVar * 0.115f;
		}
		else
			SpreadFactor = SpreadVar * 0.3f;
	}
	
	return SpreadFactor;
}

void WeaponInfo::UpdateSpreadAngles()
{
	// Check if weapon is ready
	if (IsWeaponReady() == false)
		return;

	// Check if weapon type is pistol or higher
	if (GetWeaponType(g_Local.WeaponID) < WEAPONTYPE_PISTOL)
		return;

	// Calculate spread angle
	Vector vAngles, vSpreadAngles, vSpread, vF, vR, vU;

	float flSpreadVar = GetSpreadFactor();
	float flSpreadX = UTIL_SharedRandomFloat(g_Local.RandomSeed + 1, -0.5f, 0.5f) + UTIL_SharedRandomFloat(g_Local.RandomSeed + 2, -0.5f, 0.5f);
	float flSpreadY = UTIL_SharedRandomFloat(g_Local.RandomSeed + 3, -0.5f, 0.5f) + UTIL_SharedRandomFloat(g_Local.RandomSeed + 4, -0.5f, 0.5f);

	flSpreadX *= flSpreadVar;
	flSpreadY *= flSpreadVar;

	g_pEngine->pfnAngleVectors(g_Local.ViewAngles, vF, vR, vU);
	vSpread = vF + vR * flSpreadX + vU * flSpreadY;
	EngineHelper::VectorAngles(vSpread, vSpreadAngles);
	vSpreadAngles[0] *= -1;

	VectorSubtract(g_Local.ViewAngles, vSpreadAngles, vAngles);
	
	// Apply spread
	g_Local.SpreadAngles.x = vAngles.x;
	g_Local.SpreadAngles.y = vAngles.y;
	g_Local.SpreadAngles.z = 0.0f;
}

void WeaponInfo::UpdatePunchAngles(ref_params_t* pParams)
{
	VectorCopy(pParams->punchangle, g_Local.PunchAngles);
	float flLength = (float)EngineHelper::VectorNormalize(g_Local.PunchAngles);
	float flTmp = flLength - (0.5f * flLength + 10.0f) * pParams->frametime;
	VectorScale(g_Local.PunchAngles, max(flTmp, 0.0f), g_Local.PunchAngles);
}
// ===================================================================================