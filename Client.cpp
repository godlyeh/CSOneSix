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
void CL_CreateMove(float frametime, usercmd_t* cmd, int active)
{
	g_oExport.CL_CreateMove(frametime, cmd, active);

	/*if (Variable::Wallhack == 2)
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
	}*/

	// Update Players
	if (EngineHelper::IsConnected())
	{
		g_Local.Update();
		for (int i = 0; i <= MAX_CLIENTS; ++i)
			g_Player[i].UpdateInfo();

		for (int i = MAX_CLIENTS; i < g_Local.EntityCount; ++i)
			g_Entity[i].UpdateInfo();
	}
}

void HUD_Redraw(float time, int intermission)
{
	g_oExport.HUD_Redraw(time, intermission);

	// Do stuff inside IsConnected, else you may get crashes on server join / mapchange
	if (EngineHelper::IsConnected())
	{
		// Draw ESP
		ESP::DrawESP();

		Draw::DrawString(false, 200, 200, rgb(255, 0, 0), "%i %i", g_Local.RoundTime, g_Local.Money);

		// Draw menu and console
		Menu::DrawMenu(rgb(168, 0, 0, 225), rgb(255, 168, 0, 225));
		Console::DrawConsole(rgb(168, 0, 0, 225));

		// Draw hud messages (center bottom, max set to 5)
		HudMessage::Draw();
	}
}

int HUD_Key_Event(int down, int keynum, const char *pszCurrentBinding)
{
	// Handle menu keys
	if (down && Menu::HandleKeys(keynum))
		return 0;

	// Handle console keys
	if (down && Console::HandleKeys(keynum))
		return 0;
	//MessageBox(0, Utility->StringA("%i", keynum), 0, 0);

	return g_oExport.HUD_Key_Event(down, keynum, pszCurrentBinding);
}
// ===================================================================================


// ===================================================================================
// Map change & round start
static char PreviousLevelName[MAX_PATH] = "\0";

void AtMapChange()
{
	// Reset infos
	g_Local.Reset();
}

void AtRoundStart()
{
	// Update necesarry player infos
	g_Local.Update();

	// Reset player infos
	if (g_Local.Frags == g_Local.Deaths == 0)
		g_Local.Headshots = 0;

	for (int i = 0; i <= MAX_CLIENTS; ++i)
	{
		if (g_Player[i].Frags == g_Player[i].Deaths == 0)
			g_Player[i].Headshots = 0;
	}

	// Map change
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

	g_pExport->CL_CreateMove = CL_CreateMove;
	g_pExport->HUD_Redraw = HUD_Redraw;
	g_pExport->HUD_Key_Event = HUD_Key_Event;
}

void UnhookExportTable()
{
	memcpy(g_pExport, &g_oExport, sizeof(export_t));
}
// ===================================================================================