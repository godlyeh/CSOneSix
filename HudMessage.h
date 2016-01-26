// ===================================================================================
// Hud message
#define MAX_HUD_MESSAGE 5

class HudMessageInfo
{
public:
	HudMessageInfo(char* Msg)
	{
		strcpy_s(Message, Msg);
	}

public:
	char Message[256];
	Timer Timeout = Timer(3);;
};
// ===================================================================================

// ===================================================================================
// Hud message helper
namespace HudMessage
{
	// Funcs
	void Add(char* Message, ...);
	void Clear();
	void Draw();

	// Array
	static std::vector<HudMessageInfo> HudMessageStorage;
}
// ===================================================================================