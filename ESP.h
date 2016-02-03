// ===================================================================================
// ESP handler
namespace ESP
{
	// Funcs
	std::string GetSequenceString(int PlayerID);
	color_t GetTeamColor(int PlayerID);

	void DrawPlayer(int PlayerID);
	void DrawWeapon(int EntityID);
	void DrawEntity(int EntityID);

	void DrawESP();
}
// ===================================================================================