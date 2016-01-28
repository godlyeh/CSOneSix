// ===================================================================================
// Player infos
class PlayerInfo // General player info
{
public:
	int Index;
};

class LocalPlayer : PlayerInfo // Local info
{
public:
	// Level info
	int RoundsPlayed;
	char LevelName[MAX_PATH];

public:
	void Reset();
	void Update();
};

void InitializePlayerInfos();
// ===================================================================================


// ===================================================================================
// Externals
extern LocalPlayer g_Local;
extern PlayerInfo g_Player[MAX_CLIENTS];
// ===================================================================================