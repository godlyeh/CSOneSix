// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
export_t* g_pExport = NULL;
export_t g_oExport;
// ===================================================================================


// ===================================================================================
// Export functions
void HUD_Redraw(float time, int intermission)
{
	g_oExport.HUD_Redraw(time, intermission);

	// Do stuff inside IsConnected, else you may get crashes on server join / mapchange
	if (EngineHelper::IsConnected())
	{
		Menu::DrawMenu(rgb(168, 0, 0, 225), rgb(255, 168, 0, 225));
		HudMessage::Draw();

		static Vector vTest;
		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
			vTest = g_oEngine.GetLocalPlayer()->origin;

		Vector vScreen;
		if (EngineHelper::WorldToScreen(vTest, vScreen))
			Draw::DrawString(true, true, vScreen, rgb(255, 0, 0), "Yay %.2f %.2f", vScreen[0], vScreen[1]);
		Draw::DrawString(false, 400, 200, rgb(255, 0, 0), "0x%p", g_oEngine.pTriAPI->WorldToScreen);
	}
}

int HUD_Key_Event(int down, int keynum, const char *pszCurrentBinding)
{
	if (down && Menu::HandleKeys(keynum))
		return 0;

	return g_oExport.HUD_Key_Event(down, keynum, pszCurrentBinding);
}
// ===================================================================================


// ===================================================================================
// Map change & round start
static char PreviousLevelName[MAX_PATH] = "\0";

void AtMapChange()
{
	
}

void AtRoundStart()
{
	// Map change
	strcpy_s(g_Local.LevelName, g_oEngine.pfnGetLevelName());
	if (PreviousLevelName[0] == '\0') strcpy_s(PreviousLevelName, g_Local.LevelName);
	if (_stricmp(g_Local.LevelName, PreviousLevelName))
	{
		AtMapChange();
		strcpy_s(PreviousLevelName, g_Local.LevelName);
	}

	// Clear hud messages if size is getting big
	if (HudMessage::HudMessageStorage.size() >= 10000)
		HudMessage::Clear();

	// Update screen info
	EngineHelper::UpdateScreenInfo();

	// Hud messages
	if (g_Local.RoundsPlayed == 1)		HudMessage::Add("[NewRound] Currently played %i round.", g_Local.RoundsPlayed);
	else								HudMessage::Add("[NewRound] Currently played %i rounds.", g_Local.RoundsPlayed);

	// inc round counter
	++g_Local.RoundsPlayed;
}
// ===================================================================================


// ===================================================================================
// Export table hook
void HookExportTable()
{
	DWORD dwExportPointer = Utility->FindPattern("hw.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 0C E8 ? ? ? ? E8 ? ? ? ?");

	Utility->DeleteLog("Exports.txt");
	Utility->Log("Exports.txt", "Export Pointer: 0x%p (Module: 0x%p)\n", dwExportPointer, Utility->CalcModuleOffset(dwExportPointer));

	g_pExport = (export_t*)dwExportPointer;
	memcpy(&g_oExport, g_pExport, sizeof(export_t));

	g_pExport->HUD_Redraw = HUD_Redraw;
	g_pExport->HUD_Key_Event = HUD_Key_Event;
}

void UnhookExportTable()
{
	memcpy(g_pExport, &g_oExport, sizeof(export_t));
}
// ===================================================================================