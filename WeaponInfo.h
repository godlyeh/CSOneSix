#pragma once

class CWeaponInfo
{
public:

	int m_iPenetration;
	int m_iDamage;
	int m_iBulletType;
	
	//
	float m_fRangeModifier;
	float m_fPenetrationPower;
	float m_fDistance;

	//
	bool SetWeaponData(int weaponId);
};

extern CWeaponInfo* g_pWeaponInfo;
