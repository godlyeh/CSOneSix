// ===================================================================================
// ESP handler
namespace ESP
{
	// Funcs
	color_t GetTeamColor(int PlayerID);
	bool IsWeapon(int EntityID);
	std::string GetSequenceString(int PlayerID);

	void DrawPlayer(int PlayerID);
	void DrawWeapon(int EntityID);
	void DrawEntity(int EntityID);

	void DrawESP();
}
// ===================================================================================