// ===================================================================================
// Weapon info
enum eWeaponBit : BYTE
{
	WEAPONBIT_NONE = 0,
	WEAPONBIT_USPSILENCER = 1,
	WEAPONBIT_GLOCKBURST = 2,
	WEAPONBIT_M4A1SILENCER = 4,
	WEAPONBIT_ELITERIGHT = 8,
	WEAPONBIT_FAMASBURST = 16
};

typedef struct
{
	char _0x0000[172];
	int WeaponID; //0x00AC 
	char _0x00B0[8];
	float NextAttack; //0x00B8 
	char _0x00BC[16];
	int Ammo; //0x00CC 
	char _0x00D0[8];
	int Reloading; //0x00D8 
	char _0x00DC[4];
	int MaxAmmo; //0x00E0 
	char _0x00E4[20];
	float SpreadVar; //0x00F8 
	float PredRecoil; //0x00FC 
	int Recoil; //0x0100 
	char _0x0104[16];
	float PistolBurstSpread; //0x0114 
	char _0x0118[4];
	float BurstSpread; //0x011C 
	char _0x0120[8];
	eWeaponBit WeaponBit; //0x0128 
	char _0x0129[31];
}weapon_t; //0x12C

enum eWeaponType : int
{
	WEAPONTYPE_NONE, WEAPONTYPE_MISC, WEAPONTYPE_KNIFE, WEAPONTYPE_PISTOL,
	WEAPONTYPE_SHOTGUN, WEAPONTYPE_SNIPER, WEAPONTYPE_SMG, WEAPONTYPE_RIFLE
};

enum {
	WEAPON_NONE, WEAPON_P228, WEAPON_UNKNOWN1, WEAPON_SCOUT, WEAPON_HEGRENADE,
	WEAPON_XM1014, WEAPON_C4, WEAPON_MAC10, WEAPON_AUG, WEAPON_SMOKEGRENADE,
	WEAPON_ELITE, WEAPON_FIVESEVEN, WEAPON_UMP45, WEAPON_SG550, WEAPON_GALIL,
	WEAPON_FAMAS, WEAPON_USP, WEAPON_GLOCK18, WEAPON_AWP, WEAPON_MP5,
	WEAPON_M249, WEAPON_M3, WEAPON_M4A1, WEAPON_TMP, WEAPON_G3SG1,
	WEAPON_FLASHBANG, WEAPON_DEAGLE, WEAPON_SG552, WEAPON_AK47, WEAPON_KNIFE,
	WEAPON_P90
};
// ===================================================================================

// ===================================================================================
// Weapon list handler
namespace WeaponInfo
{
	// Offs
	static DWORD dwGetWeaponByID = 0;

	// Funcs
	weapon_t* GetWeaponByID(int WeaponID);
	bool IsWeaponReady();
	eWeaponType GetWeaponType(int WeaponID);
	void Init();

	// Spread and recoil
	float GetSpreadFactor();
	void UpdateSpreadAngles();
	void UpdatePunchAngles(ref_params_t *pParams);
};
// ===================================================================================