// ===================================================================================
// Player infos
typedef struct
{
	short TeamNumber; //0x0000 
	char TeamName[10]; //0x0002 
	char _0x000C[92];
}teaminfo_t;//Size=0x0068

class EntityInfo // General entity info
{
public:
	// Entity info
	char Name[32];
	bool Alive;

	// Player info
	bool Valid;
	int Index;
	teaminfo_t* Team;

	// Entity info
	bool IsHostage;

	// Weapon
	char Weapon[64];

	// Frag info
	int Frags;
	int Deaths;
	int Headshots; // only as accurate as when you enabled hack since its not stored anywhere

	// Positions
	Vector Angles;
	Vector Origin;
	Vector RadarCoord; // Team only
	Vector Mins, Maxs;

public:
	void UpdateInfo();

private:
	DWORD dwGetPlayerName = 0;
	DWORD dwGetPlayerTeam = 0;
	char* GetPlayerName();
	char* GetWeaponName(char* WeaponName);
	teaminfo_t* GetPlayerTeam();
};

class LocalPlayer : public EntityInfo // Local info
{
public:
	// Client info
	int Health;
	int Armor;
	bool IsOnTrain;
	int Money;
	int RoundTime;
	int RoundsPlayed;
	char LevelName[MAX_PATH];

	// Entity info
	int EntityCount;

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
// ===================================================================================