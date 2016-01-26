// ===================================================================================
// Player infos
class PlayerInfo
{
public:

};

class LocalPlayer : PlayerInfo
{
public:
	// Level info
	int RoundsPlayed;
	char LevelName[MAX_PATH];
};
// ===================================================================================


// ===================================================================================
// Externals
extern LocalPlayer g_Local;
extern PlayerInfo g_Player[MAX_CLIENTS];
// ===================================================================================