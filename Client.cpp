// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
globalvars_t* g_pGlobals = NULL;
export_t* g_pExport = NULL;
export_t g_oExport;
// ===================================================================================


// ===================================================================================
// Export functions
float flTest = 0;

void CL_CreateMove(float frametime, usercmd_t* cmd, int active)
{
	g_oExport.CL_CreateMove(frametime, cmd, active);

	/*if (Variable::Wallhack == 2)
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
	}*/

	if (EngineHelper::IsConnected())
	{
		// Update Players
		g_Local.Update(frametime);
		for (int i = 0; i <= MAX_CLIENTS; ++i)
			g_Player[i].UpdateInfo();

		for (int i = 0; i < g_Local.EntityCount; ++i)
			g_Entity[i].UpdateInfo();

		// Recoil & Spread
		//if (WeaponInfo::GetWeaponType(g_Local.WeaponID) != WEAPONTYPE_PISTOL)
		//	WeaponInfo::UpdateSpreadAngles();

		// Aimbot
		if (Variable::Aimbot)
		{
			Aimbot::CL_CreateMove(cmd);
			if (cmd->buttons &IN_ATTACK)
			{
				cmd->viewangles.x += g_Local.SpreadAngles.x;
				cmd->viewangles.y += g_Local.SpreadAngles.y;
				cmd->viewangles.x -= g_Local.PunchAngles.x * 2;
				cmd->viewangles.y -= g_Local.PunchAngles.y * 2;
			}
		}

		// Pistol rapid fire
		if (Variable::PistolRapidFire && WeaponInfo::IsWeaponReady())
		{
			weapon_t* pWeapon = WeaponInfo::GetWeaponByID(g_Local.WeaponID);
			if (WeaponInfo::GetWeaponType(pWeapon->WeaponID) == WEAPONTYPE_PISTOL)
			{
				if (pWeapon->NextAttack > 0.0f)
					cmd->buttons &= ~IN_ATTACK;
			}
		}

		g_pMovement->Fix(cmd, g_Local.LocalViewAngles);
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
		
		//weapon_t* pWeapon = WeaponInfo::GetWeaponByID(g_Local.WeaponID);
		//if (pWeapon)
			Draw::DrawString(false, 200, 200, rgb(255, 0, 0), "(%.2f %.2f %.2f) %.2f (%.2f %.2f)", g_Local.Velocity.x, g_Local.Velocity.y, g_Local.Velocity.z, g_Local.FrameTime, g_Local.Angles.x, g_Local.Angles.y);

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

	return g_oExport.HUD_Key_Event(down, keynum, pszCurrentBinding);
}

void V_CalcRefdef(ref_params_t *pParams)
{
	VectorCopy(pParams->vieworg, g_Local.EyePosition);
	VectorCopy(pParams->cl_viewangles, g_Local.LocalViewAngles);
	WeaponInfo::UpdatePunchAngles(pParams);

	if (pParams->cmd->buttons &IN_ATTACK)
	{
		pParams->punchangle[0] -= g_Local.PunchAngles.x * 2;
		pParams->punchangle[1] -= g_Local.PunchAngles.y * 2;
		pParams->punchangle[0] += g_Local.SpreadAngles.x;
		pParams->punchangle[1] += g_Local.SpreadAngles.y;
	}

	if (Aimbot::AimTarget != INVALID_TARGET)
		VectorCopy(Aimbot::AimAngles, pParams->cl_viewangles);

	// Call original function
	g_oExport.V_CalcRefdef(pParams);

	for (int i = 0; i <= MAX_CLIENTS; ++i)
	{
		g_Player[i].bGotBoneMatrix = false;

		// Reset trace (not fully necesarry unless ur doing something with dead ents)
		g_Player[i].AimOriginVisible = false;
		for (int x = 0; x < MAXSTUDIOBONES; ++x)
			g_Player[i].BoneVisible[x] = false;
	}
}

void HUD_PostRunCmd(local_state_s *from, local_state_s *to, usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed)
{
	g_oExport.HUD_PostRunCmd(from, to, cmd, runfuncs, time, random_seed);
	if (runfuncs)
	{
		g_Local.FOV = to->client.fov;
		g_Local.WeaponID = to->client.m_iId;
		g_Local.Ammo = to->weapondata[g_Local.WeaponID].m_iClip;
		VectorCopy(to->client.velocity, g_Local.Velocity);
		VectorCopy(cmd->viewangles, g_Local.ViewAngles);
		g_Local.Flags = to->client.flags;
		g_Local.RandomSeed = random_seed;

		if (WeaponInfo::IsWeaponReady())
		{
			//if (to->weapondata[g_Local.WeaponID].m_flNextPrimaryAttack <= 0.0f)
				WeaponInfo::UpdateSpreadAngles();
		}
	}
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
	g_Local.Update(0);

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
	DWORD dwGlobals = Utility->FindPattern("client.dll", "A1 ? ? ? ? 8D 48 34 8D 50 40 D9 5C 24 1C");
	DWORD dwExportPointer = Utility->FindPattern("hw.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 0C E8 ? ? ? ? E8 ? ? ? ?");

	g_pGlobals = (globalvars_t*)*(PDWORD)dwGlobals;
	g_pExport = (export_t*)dwExportPointer;
	memcpy(&g_oExport, g_pExport, sizeof(export_t));

	Utility->DeleteLog("Client.txt");
	Utility->Log("Client.txt", "Export Pointer: 0x%p (Module: 0x%p)\n", g_pExport, Utility->CalcModuleOffset((DWORD)g_pExport));
	Utility->Log("Client.txt", "Globals Pointer: 0x%p (Module: 0x%p)\n", g_pGlobals, Utility->CalcModuleOffset((DWORD)g_pGlobals));

	g_pExport->CL_CreateMove = CL_CreateMove;
	g_pExport->HUD_Redraw = HUD_Redraw;
	g_pExport->HUD_Key_Event = HUD_Key_Event;
	g_pExport->V_CalcRefdef = V_CalcRefdef;
	g_pExport->HUD_PostRunCmd = HUD_PostRunCmd;
}

void UnhookExportTable()
{
	memcpy(g_pExport, &g_oExport, sizeof(export_t));
}
// ===================================================================================