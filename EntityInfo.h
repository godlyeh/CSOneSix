// ===================================================================================
// Player infos
#define MAX_TEAM_NAME 16

typedef struct
{
	short TeamNumber; //0x0000 
	char TeamName[MAX_TEAM_NAME]; //0x0002 
	char _0x000C[86];
}teaminfo_t;//Size=0x0068

class EntityInfo // General entity info
{
public:
	// Entity info
	char Name[32];
	bool Alive;

	// Player info
	bool IsPlayer;
	bool Visible;
	bool Valid;
	bool Ducking;
	int Index;
	int Sequence;
	int GaitSequence;
	teaminfo_t* Team;

	// Entity info
	bool IsHostage;

	// Weapon
	char Weapon[128];

	// Frag info
	int Frags;
	int Deaths;
	int Headshots; // only as accurate as when you enabled hack since its not stored anywhere

	// Positions
	Vector Angles;
	Vector Origin;
	Vector RadarCoord; // Team only
	Vector Mins, Maxs;

	// Aiming
	Vector AimOrigin;
	bool AimOriginVisible;

	// Bone
	bool bGotBoneMatrix;
	TransformMatrix BoneMatrix;
	bool BoneVisible[MAXSTUDIOBONES];

public:
	void UpdateInfo();

private:
	DWORD dwGetPlayerName = 0;
	DWORD dwGetPlayerTeam = 0;
	char* GetPlayerName();
	char* GetPlayerWeaponName(char* WeaponName);
	char* GetWeaponName(char* WeaponName);
	teaminfo_t* GetPlayerTeam();
};

class LocalPlayer : public EntityInfo // Local info
{
public:
	// Client info
	int WeaponID;
	int Health;
	int Armor;
	float FOV;
	bool IsOnTrain;
	int Money;
	int RoundTime;
	int RoundsPlayed;
	char LevelName[MAX_PATH];

	// Entity info
	int EntityCount;

	// Location
	Vector EyePosition;

public:
	void Reset();
	void Update();
};

void InitializePlayerInfos();
// ===================================================================================


// ===================================================================================
// Externals
extern LocalPlayer g_Local;
extern EntityInfo g_Player[MAX_CLIENTS + 1];
extern EntityInfo g_Entity[4096];
extern int *g_piEntityCount;
extern playermove_t* g_pPlayerMove;
// ===================================================================================