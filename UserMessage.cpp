// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
usermsg_t* g_pUserMsg;

pfnUserMsgHook oCZCareer = NULL;
pfnUserMsgHook oReqState = NULL;
pfnUserMsgHook oVoiceMask = NULL;
pfnUserMsgHook oShowMenu = NULL;
pfnUserMsgHook oScenario = NULL;
pfnUserMsgHook oTaskTime = NULL;
pfnUserMsgHook oBarTime2 = NULL;
pfnUserMsgHook oBarTime = NULL;
pfnUserMsgHook oRoundTime = NULL;
pfnUserMsgHook oBlinkAcct = NULL;
pfnUserMsgHook oMoney = NULL;
pfnUserMsgHook oStatusIcon = NULL;
pfnUserMsgHook oTextMsg = NULL;
pfnUserMsgHook oSecAmmoIcon = NULL;
pfnUserMsgHook oSecAmmoVal = NULL;
pfnUserMsgHook oDeathMsg = NULL;
pfnUserMsgHook oStatusValue = NULL;
pfnUserMsgHook oStatusText = NULL;
pfnUserMsgHook oGameTitle = NULL;
pfnUserMsgHook oHudTextArgs = NULL;
pfnUserMsgHook oHudTextPro = NULL;
pfnUserMsgHook oHudText = NULL;
pfnUserMsgHook oFlashBat = NULL;
pfnUserMsgHook oFlashlight = NULL;
pfnUserMsgHook oArmorType = NULL;
pfnUserMsgHook oBattery = NULL;
pfnUserMsgHook oTrain = NULL;
pfnUserMsgHook oGeiger = NULL;
pfnUserMsgHook oSendAudio = NULL;
pfnUserMsgHook oSayText = NULL;
pfnUserMsgHook oReceiveW = NULL;
pfnUserMsgHook oClCorpse = NULL;
pfnUserMsgHook oScoreAttrib = NULL;
pfnUserMsgHook oRadar = NULL;
pfnUserMsgHook oDamage = NULL;
pfnUserMsgHook oHealth = NULL;
pfnUserMsgHook oCrosshair = NULL;
pfnUserMsgHook oAmmoX = NULL;
pfnUserMsgHook oHideWeapon = NULL;
pfnUserMsgHook oItemPickup = NULL;
pfnUserMsgHook oWeapPickup = NULL;
pfnUserMsgHook oAmmoPickup = NULL;
pfnUserMsgHook oWeaponList = NULL;
pfnUserMsgHook oCurWeapon = NULL;
pfnUserMsgHook oNVGToggle = NULL;
pfnUserMsgHook oItemStatus = NULL;
pfnUserMsgHook oBotProgress = NULL;
pfnUserMsgHook oSpecHealth2 = NULL;
pfnUserMsgHook oBuyClose = NULL;
pfnUserMsgHook oTutorClose = NULL;
pfnUserMsgHook oTutorState = NULL;
pfnUserMsgHook oTutorLine = NULL;
pfnUserMsgHook oTutorText = NULL;
pfnUserMsgHook oVGUIMenu = NULL;
pfnUserMsgHook oForceCam = NULL;
pfnUserMsgHook oAllowSpec = NULL;
pfnUserMsgHook oSpectator = NULL;
pfnUserMsgHook oLocation = NULL;
pfnUserMsgHook oTeamInfo = NULL;
pfnUserMsgHook oTeamScore = NULL;
pfnUserMsgHook oScoreInfo = NULL;
pfnUserMsgHook oServerName = NULL;
pfnUserMsgHook oRandomPC = NULL;
pfnUserMsgHook oBuildSt = NULL;
pfnUserMsgHook oMOTD = NULL;
pfnUserMsgHook oDetpack = NULL;
pfnUserMsgHook oFeign = NULL;
pfnUserMsgHook oTeamNames = NULL;
pfnUserMsgHook oShowTimer = NULL;
pfnUserMsgHook oFog = NULL;
pfnUserMsgHook oBrass = NULL;
pfnUserMsgHook oBotVoice = NULL;
pfnUserMsgHook oShadowIdx = NULL;
pfnUserMsgHook oCZCareerHUD = NULL;
pfnUserMsgHook oHostageK = NULL;
pfnUserMsgHook oHostagePos = NULL;
pfnUserMsgHook oADStop = NULL;
pfnUserMsgHook oBombPickup = NULL;
pfnUserMsgHook oBombDrop = NULL;
pfnUserMsgHook oReloadSound = NULL;
pfnUserMsgHook oConcuss = NULL;
pfnUserMsgHook oSpecHealth = NULL;
pfnUserMsgHook oHLTV = NULL;
pfnUserMsgHook oSetFOV = NULL;
pfnUserMsgHook oViewMode = NULL;
pfnUserMsgHook oInitHUD = NULL;
pfnUserMsgHook oGameMode = NULL;
pfnUserMsgHook oResetHUD = NULL;
pfnUserMsgHook oLogo = NULL;
pfnUserMsgHook oScreenFade = NULL;
pfnUserMsgHook oScreenShake = NULL;
// ===================================================================================


// ===================================================================================
// UserMsg
int Hooked_CZCareer(const char *pszName, int iSize, void *pbuf)
{
	return oCZCareer(pszName, iSize, pbuf);
}

int Hooked_ReqState(const char *pszName, int iSize, void *pbuf)
{
	return oReqState(pszName, iSize, pbuf);
}

int Hooked_VoiceMask(const char *pszName, int iSize, void *pbuf)
{
	return oVoiceMask(pszName, iSize, pbuf);
}

int Hooked_ShowMenu(const char *pszName, int iSize, void *pbuf)
{
	return oShowMenu(pszName, iSize, pbuf);
}

int Hooked_Scenario(const char *pszName, int iSize, void *pbuf)
{
	return oScenario(pszName, iSize, pbuf);
}

int Hooked_TaskTime(const char *pszName, int iSize, void *pbuf)
{
	return oTaskTime(pszName, iSize, pbuf);
}

int Hooked_BarTime2(const char *pszName, int iSize, void *pbuf)
{
	return oBarTime2(pszName, iSize, pbuf);
}

int Hooked_BarTime(const char *pszName, int iSize, void *pbuf)
{
	return oBarTime(pszName, iSize, pbuf);
}

int Hooked_RoundTime(const char *pszName, int iSize, void *pbuf)
{
	return oRoundTime(pszName, iSize, pbuf);
}

int Hooked_BlinkAcct(const char *pszName, int iSize, void *pbuf)
{
	return oBlinkAcct(pszName, iSize, pbuf);
}

int Hooked_Money(const char *pszName, int iSize, void *pbuf)
{
	return oMoney(pszName, iSize, pbuf);
}

int Hooked_StatusIcon(const char *pszName, int iSize, void *pbuf)
{
	return oStatusIcon(pszName, iSize, pbuf);
}

int Hooked_TextMsg(const char *pszName, int iSize, void *pbuf)
{
	return oTextMsg(pszName, iSize, pbuf);
}

int Hooked_SecAmmoIcon(const char *pszName, int iSize, void *pbuf)
{
	return oSecAmmoIcon(pszName, iSize, pbuf);
}

int Hooked_SecAmmoVal(const char *pszName, int iSize, void *pbuf)
{
	return oSecAmmoVal(pszName, iSize, pbuf);
}

int Hooked_DeathMsg(const char *pszName, int iSize, void *pbuf)
{
	return oDeathMsg(pszName, iSize, pbuf);
}

int Hooked_StatusValue(const char *pszName, int iSize, void *pbuf)
{
	return oStatusValue(pszName, iSize, pbuf);
}

int Hooked_StatusText(const char *pszName, int iSize, void *pbuf)
{
	return oStatusText(pszName, iSize, pbuf);
}

int Hooked_GameTitle(const char *pszName, int iSize, void *pbuf)
{
	return oGameTitle(pszName, iSize, pbuf);
}

int Hooked_HudTextArgs(const char *pszName, int iSize, void *pbuf)
{
	return oHudTextArgs(pszName, iSize, pbuf);
}

int Hooked_HudTextPro(const char *pszName, int iSize, void *pbuf)
{
	return oHudTextPro(pszName, iSize, pbuf);
}

int Hooked_HudText(const char *pszName, int iSize, void *pbuf)
{
	return oHudText(pszName, iSize, pbuf);
}

int Hooked_FlashBat(const char *pszName, int iSize, void *pbuf)
{
	return oFlashBat(pszName, iSize, pbuf);
}

int Hooked_Flashlight(const char *pszName, int iSize, void *pbuf)
{
	return oFlashlight(pszName, iSize, pbuf);
}

int Hooked_ArmorType(const char *pszName, int iSize, void *pbuf)
{
	return oArmorType(pszName, iSize, pbuf);
}

int Hooked_Battery(const char *pszName, int iSize, void *pbuf)
{
	return oBattery(pszName, iSize, pbuf);
}

int Hooked_Train(const char *pszName, int iSize, void *pbuf)
{
	return oTrain(pszName, iSize, pbuf);
}

int Hooked_Geiger(const char *pszName, int iSize, void *pbuf)
{
	return oGeiger(pszName, iSize, pbuf);
}

int Hooked_SendAudio(const char *pszName, int iSize, void *pbuf)
{
	return oSendAudio(pszName, iSize, pbuf);
}

int Hooked_SayText(const char *pszName, int iSize, void *pbuf)
{
	return oSayText(pszName, iSize, pbuf);
}

int Hooked_ReceiveW(const char *pszName, int iSize, void *pbuf)
{
	return oReceiveW(pszName, iSize, pbuf);
}

int Hooked_ClCorpse(const char *pszName, int iSize, void *pbuf)
{
	return oClCorpse(pszName, iSize, pbuf);
}

int Hooked_ScoreAttrib(const char *pszName, int iSize, void *pbuf)
{
	return oScoreAttrib(pszName, iSize, pbuf);
}

int Hooked_Radar(const char *pszName, int iSize, void *pbuf)
{
	return oRadar(pszName, iSize, pbuf);
}

int Hooked_Damage(const char *pszName, int iSize, void *pbuf)
{
	return oDamage(pszName, iSize, pbuf);
}

int Hooked_Health(const char *pszName, int iSize, void *pbuf)
{
	return oHealth(pszName, iSize, pbuf);
}

int Hooked_Crosshair(const char *pszName, int iSize, void *pbuf)
{
	return oCrosshair(pszName, iSize, pbuf);
}

int Hooked_AmmoX(const char *pszName, int iSize, void *pbuf)
{
	return oAmmoX(pszName, iSize, pbuf);
}

int Hooked_HideWeapon(const char *pszName, int iSize, void *pbuf)
{
	return oHideWeapon(pszName, iSize, pbuf);
}

int Hooked_ItemPickup(const char *pszName, int iSize, void *pbuf)
{
	return oItemPickup(pszName, iSize, pbuf);
}

int Hooked_WeapPickup(const char *pszName, int iSize, void *pbuf)
{
	return oWeapPickup(pszName, iSize, pbuf);
}

int Hooked_AmmoPickup(const char *pszName, int iSize, void *pbuf)
{
	return oAmmoPickup(pszName, iSize, pbuf);
}

int Hooked_WeaponList(const char *pszName, int iSize, void *pbuf)
{
	return oWeaponList(pszName, iSize, pbuf);
}

int Hooked_CurWeapon(const char *pszName, int iSize, void *pbuf)
{
	return oCurWeapon(pszName, iSize, pbuf);
}

int Hooked_NVGToggle(const char *pszName, int iSize, void *pbuf)
{
	return oNVGToggle(pszName, iSize, pbuf);
}

int Hooked_ItemStatus(const char *pszName, int iSize, void *pbuf)
{
	return oItemStatus(pszName, iSize, pbuf);
}

int Hooked_BotProgress(const char *pszName, int iSize, void *pbuf)
{
	return oBotProgress(pszName, iSize, pbuf);
}

int Hooked_SpecHealth2(const char *pszName, int iSize, void *pbuf)
{
	return oSpecHealth2(pszName, iSize, pbuf);
}

int Hooked_BuyClose(const char *pszName, int iSize, void *pbuf)
{
	return oBuyClose(pszName, iSize, pbuf);
}

int Hooked_TutorClose(const char *pszName, int iSize, void *pbuf)
{
	return oTutorClose(pszName, iSize, pbuf);
}

int Hooked_TutorState(const char *pszName, int iSize, void *pbuf)
{
	return oTutorState(pszName, iSize, pbuf);
}

int Hooked_TutorLine(const char *pszName, int iSize, void *pbuf)
{
	return oTutorLine(pszName, iSize, pbuf);
}

int Hooked_TutorText(const char *pszName, int iSize, void *pbuf)
{
	return oTutorText(pszName, iSize, pbuf);
}

int Hooked_VGUIMenu(const char *pszName, int iSize, void *pbuf)
{
	return oVGUIMenu(pszName, iSize, pbuf);
}

int Hooked_ForceCam(const char *pszName, int iSize, void *pbuf)
{
	return oForceCam(pszName, iSize, pbuf);
}

int Hooked_AllowSpec(const char *pszName, int iSize, void *pbuf)
{
	return oAllowSpec(pszName, iSize, pbuf);
}

int Hooked_Spectator(const char *pszName, int iSize, void *pbuf)
{
	return oSpectator(pszName, iSize, pbuf);
}

int Hooked_Location(const char *pszName, int iSize, void *pbuf)
{
	return oLocation(pszName, iSize, pbuf);
}

int Hooked_TeamInfo(const char *pszName, int iSize, void *pbuf)
{
	return oTeamInfo(pszName, iSize, pbuf);
}

int Hooked_TeamScore(const char *pszName, int iSize, void *pbuf)
{
	return oTeamScore(pszName, iSize, pbuf);
}

int Hooked_ScoreInfo(const char *pszName, int iSize, void *pbuf)
{
	return oScoreInfo(pszName, iSize, pbuf);
}

int Hooked_ServerName(const char *pszName, int iSize, void *pbuf)
{
	return oServerName(pszName, iSize, pbuf);
}

int Hooked_RandomPC(const char *pszName, int iSize, void *pbuf)
{
	return oRandomPC(pszName, iSize, pbuf);
}

int Hooked_BuildSt(const char *pszName, int iSize, void *pbuf)
{
	return oBuildSt(pszName, iSize, pbuf);
}

int Hooked_MOTD(const char *pszName, int iSize, void *pbuf)
{
	return oMOTD(pszName, iSize, pbuf);
}

int Hooked_Detpack(const char *pszName, int iSize, void *pbuf)
{
	return oDetpack(pszName, iSize, pbuf);
}

int Hooked_Feign(const char *pszName, int iSize, void *pbuf)
{
	return oFeign(pszName, iSize, pbuf);
}

int Hooked_TeamNames(const char *pszName, int iSize, void *pbuf)
{
	return oTeamNames(pszName, iSize, pbuf);
}

int Hooked_ShowTimer(const char *pszName, int iSize, void *pbuf)
{
	return oShowTimer(pszName, iSize, pbuf);
}

int Hooked_Fog(const char *pszName, int iSize, void *pbuf)
{
	return oFog(pszName, iSize, pbuf);
}

int Hooked_Brass(const char *pszName, int iSize, void *pbuf)
{
	return oBrass(pszName, iSize, pbuf);
}

int Hooked_BotVoice(const char *pszName, int iSize, void *pbuf)
{
	return oBotVoice(pszName, iSize, pbuf);
}

int Hooked_ShadowIdx(const char *pszName, int iSize, void *pbuf)
{
	return oShadowIdx(pszName, iSize, pbuf);
}

int Hooked_CZCareerHUD(const char *pszName, int iSize, void *pbuf)
{
	return oCZCareerHUD(pszName, iSize, pbuf);
}

int Hooked_HostageK(const char *pszName, int iSize, void *pbuf)
{
	return oHostageK(pszName, iSize, pbuf);
}

int Hooked_HostagePos(const char *pszName, int iSize, void *pbuf)
{
	return oHostagePos(pszName, iSize, pbuf);
}

int Hooked_ADStop(const char *pszName, int iSize, void *pbuf)
{
	return oADStop(pszName, iSize, pbuf);
}

int Hooked_BombPickup(const char *pszName, int iSize, void *pbuf)
{
	return oBombPickup(pszName, iSize, pbuf);
}

int Hooked_BombDrop(const char *pszName, int iSize, void *pbuf)
{
	return oBombDrop(pszName, iSize, pbuf);
}

int Hooked_ReloadSound(const char *pszName, int iSize, void *pbuf)
{
	return oReloadSound(pszName, iSize, pbuf);
}

int Hooked_Concuss(const char *pszName, int iSize, void *pbuf)
{
	return oConcuss(pszName, iSize, pbuf);
}

int Hooked_SpecHealth(const char *pszName, int iSize, void *pbuf)
{
	return oSpecHealth(pszName, iSize, pbuf);
}

int Hooked_HLTV(const char *pszName, int iSize, void *pbuf)
{
	return oHLTV(pszName, iSize, pbuf);
}

int Hooked_SetFOV(const char *pszName, int iSize, void *pbuf)
{
	return oSetFOV(pszName, iSize, pbuf);
}

int Hooked_ViewMode(const char *pszName, int iSize, void *pbuf)
{
	return oViewMode(pszName, iSize, pbuf);
}

int Hooked_InitHUD(const char *pszName, int iSize, void *pbuf)
{
	return oInitHUD(pszName, iSize, pbuf);
}

int Hooked_GameMode(const char *pszName, int iSize, void *pbuf)
{
	return oGameMode(pszName, iSize, pbuf);
}

int Hooked_ResetHUD(const char *pszName, int iSize, void *pbuf)
{
	AtRoundStart();
	return oResetHUD(pszName, iSize, pbuf);
}

int Hooked_Logo(const char *pszName, int iSize, void *pbuf)
{
	return oLogo(pszName, iSize, pbuf);
}

int Hooked_ScreenFade(const char *pszName, int iSize, void *pbuf)
{
	return oScreenFade(pszName, iSize, pbuf);
}

int Hooked_ScreenShake(const char *pszName, int iSize, void *pbuf)
{
	return oScreenShake(pszName, iSize, pbuf);
}
// ===================================================================================


// ===================================================================================
// UserMsg list hook
void HookUserMsgList()
{
	DWORD dwUserMsgPointer = Utility->FindPattern("hw.dll", "8B 35 ? ? ? ? 83 C4 30 85 F6");
	dwUserMsgPointer = *(PDWORD)dwUserMsgPointer;

	Utility->DeleteLog("UserMsg.txt");
	Utility->Log("UserMsg.txt", "UserMsg List Pointer: 0x%p (Module: 0x%p)\n", dwUserMsgPointer, Utility->CalcModuleOffset(dwUserMsgPointer));

	g_pUserMsg = (usermsg_t*)dwUserMsgPointer;

	while (g_pUserMsg)
	{
		Utility->Log("UserMsg.txt", " [UserMsgList][0x%p] %s = 0x%p (Module: 0x%p)\n", g_pUserMsg, g_pUserMsg->Name, g_pUserMsg->Function, Utility->CalcModuleOffset((DWORD)g_pUserMsg));

#define HookUserMsg(name) { if (!_stricmp(g_pUserMsg->Name, #name)) { \
								o##name = (pfnUserMsgHook)g_pUserMsg->Function; \
								HOOK(&g_pUserMsg->Function, Hooked_##name); } }
		
		//Utility->Log("UserMsg.txt", "HookUserMsg(%s);\n", g_pUserMsg->Name);
		HookUserMsg(CZCareer);
		HookUserMsg(ReqState);
		HookUserMsg(VoiceMask);
		HookUserMsg(ShowMenu);
		HookUserMsg(Scenario);
		HookUserMsg(TaskTime);
		HookUserMsg(BarTime2);
		HookUserMsg(BarTime);
		HookUserMsg(RoundTime);
		HookUserMsg(BlinkAcct);
		HookUserMsg(Money);
		HookUserMsg(StatusIcon);
		HookUserMsg(TextMsg);
		HookUserMsg(SecAmmoIcon);
		HookUserMsg(SecAmmoVal);
		HookUserMsg(DeathMsg);
		HookUserMsg(StatusValue);
		HookUserMsg(StatusText);
		HookUserMsg(GameTitle);
		HookUserMsg(HudTextArgs);
		HookUserMsg(HudTextPro);
		HookUserMsg(HudText);
		HookUserMsg(FlashBat);
		HookUserMsg(Flashlight);
		HookUserMsg(ArmorType);
		HookUserMsg(Battery);
		HookUserMsg(Train);
		HookUserMsg(Geiger);
		HookUserMsg(SendAudio);
		HookUserMsg(SayText);
		HookUserMsg(ReceiveW);
		HookUserMsg(ClCorpse);
		HookUserMsg(ScoreAttrib);
		HookUserMsg(Radar);
		HookUserMsg(Damage);
		HookUserMsg(Health);
		HookUserMsg(Crosshair);
		HookUserMsg(AmmoX);
		HookUserMsg(HideWeapon);
		HookUserMsg(ItemPickup);
		HookUserMsg(WeapPickup);
		HookUserMsg(AmmoPickup);
		HookUserMsg(WeaponList);
		HookUserMsg(CurWeapon);
		HookUserMsg(NVGToggle);
		HookUserMsg(ItemStatus);
		HookUserMsg(BotProgress);
		HookUserMsg(SpecHealth2);
		HookUserMsg(BuyClose);
		HookUserMsg(TutorClose);
		HookUserMsg(TutorState);
		HookUserMsg(TutorLine);
		HookUserMsg(TutorText);
		HookUserMsg(VGUIMenu);
		HookUserMsg(ForceCam);
		HookUserMsg(AllowSpec);
		HookUserMsg(Spectator);
		HookUserMsg(Location);
		HookUserMsg(TeamInfo);
		HookUserMsg(TeamScore);
		HookUserMsg(ScoreInfo);
		HookUserMsg(ServerName);
		HookUserMsg(RandomPC);
		HookUserMsg(BuildSt);
		HookUserMsg(MOTD);
		HookUserMsg(Detpack);
		HookUserMsg(Feign);
		HookUserMsg(TeamNames);
		HookUserMsg(ShowTimer);
		HookUserMsg(Fog);
		HookUserMsg(Brass);
		HookUserMsg(BotVoice);
		HookUserMsg(ShadowIdx);
		HookUserMsg(CZCareerHUD);
		HookUserMsg(HostageK);
		HookUserMsg(HostagePos);
		HookUserMsg(ADStop);
		HookUserMsg(BombPickup);
		HookUserMsg(BombDrop);
		HookUserMsg(ReloadSound);
		HookUserMsg(Concuss);
		HookUserMsg(SpecHealth);
		HookUserMsg(HLTV);
		HookUserMsg(SetFOV);
		HookUserMsg(ViewMode);
		HookUserMsg(InitHUD);
		HookUserMsg(GameMode);
		HookUserMsg(ResetHUD);
		HookUserMsg(Logo);
		HookUserMsg(ScreenFade);
		HookUserMsg(ScreenShake);

		g_pUserMsg = g_pUserMsg->Next;
	}

	g_pUserMsg = (usermsg_t*)dwUserMsgPointer;
}
// ===================================================================================