// ===================================================================================
// Player infos
class PlayerInfo // General player info
{
public:
	// Info
	char Name[32];
	bool Alive;
	bool Valid;
	int Index;

	// Positions
	Vector Angles;
	Vector Origin;

public:
	void UpdateInfo();
};

class LocalPlayer : PlayerInfo // Local info
{
public:
	// Level info
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
extern PlayerInfo g_Player[MAX_CLIENTS + 1];
extern int *g_piEntityCount;
// ===================================================================================