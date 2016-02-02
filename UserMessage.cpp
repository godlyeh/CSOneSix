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
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message supplies certain updates to the player regarding Condition Zero single-player missions.
		Note: See the CZCareer page for more information. (https://wiki.alliedmods.net/CZCareer)
		Note: Using an invalid type has no repercussions whatsoever. Therefore, you can use this to make your own custom communications (you can send any number of arguments of any type after the first string).
		Note: The Type argument is case-sensitive.
		Note: This event does nothing in CS and CZ multiplayer.
	*/
	BEGIN_READ(pbuf, iSize);
	char* Type = READ_STRING();
	
	return oCZCareer(pszName, iSize, pbuf);
}

int Hooked_ReqState(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		Note: No Information is available for this message.
		Note: This message has no arguments.
	*/
	return oReqState(pszName, iSize, pbuf);
}

int Hooked_VoiceMask(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message tells a client whom they can hear over the microphone.
	BEGIN_READ(pbuf, iSize);
	int AudiblePlayersIndexBitSum = READ_LONG();
	int ServerBannedPlayersIndexBitSum = READ_LONG();

	return oVoiceMask(pszName, iSize, pbuf);
}

int Hooked_ShowMenu(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message displays a "menu" to a player (text on the left side of the screen). It acts like AMXX's show_menu (in fact, this is how AMXX shows a menu).
		Note: Multipart should be 1 if your menu takes up multiple messages (i.e.: string is too big to fit into one). On the final message, Multipart should be 0.
	*/
	BEGIN_READ(pbuf, iSize);
	int KeysBitSum = READ_SHORT();
	int Time = READ_CHAR();
	int Multipart = READ_BYTE();
	char* Text = READ_STRING();

	return oShowMenu(pszName, iSize, pbuf);
}

int Hooked_Scenario(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		If Active is 0, this display will be hidden. If Active is 1, this displays Sprite (valid names listed in sprites/hud.txt) to the right of the round timer with an alpha value of Alpha (100-255).
		If FlashRate is nonzero, then the sprite will flash from the given alpha to an alpha of 100, at a rate of FlashRate (measured in ???).
		This is used by CZ to display how many hostages remain unrescued, and also to display the ticking bomb when it is planted.

		Scenario message in CS, using the following parameters: 1, d_mp5navy, 150
		Note: If Active is 0, don't send any other arguments afterwards. Also, you don't need to send either short if FlashRate is just going to be 0.
		Note: This works in both CS and CZ!
		Note: In CZ (and possibly CS), if someone respawns after the bomb has been planted, their Scenario event will not work at all until the next round.
	*/
	BEGIN_READ(pbuf, iSize);
	int Active = READ_BYTE();
	char* Sprite = READ_STRING();
	int Alpha = READ_BYTE();
	int FlashRate = READ_SHORT();
	int FlashDelay = READ_SHORT();

	return oScenario(pszName, iSize, pbuf);
}

int Hooked_TaskTime(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message displays a secondary timer above the round timer. It is used for Condition Zero singleplayer missions.
		If Time is -1, the timer dissappears. If Time is any other negative value, it is displayed as green instead of yellow, and considered positive.
		If Active is true, timer counts down. Otherwise, it is paused.
		If Fade is above zero, the timer will slowly fade out after that many seconds have passed (even if the timer is inactive).
		Note: This event can only be used on missions that have an objective requiring a secondary timer!
	*/
	BEGIN_READ(pbuf, iSize);
	int Time = READ_SHORT();
	int Active = READ_BYTE();
	int Fade = READ_BYTE();

	return oTaskTime(pszName, iSize, pbuf);
}

int Hooked_BarTime2(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		The message is the same as BarTime, but StartPercent specifies how much of the bar is (already) filled.
		Note: Display time can be calculated with this formula: (1 - (StartPercent / 100)) / Duration
	*/
	BEGIN_READ(pbuf, iSize);
	int Duration = READ_SHORT();
	int StartPercent = READ_SHORT();

	return oBarTime2(pszName, iSize, pbuf);
}

int Hooked_BarTime(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message draws a HUD progress bar which is filled from 0% to 100% for the time Duration seconds. Once the bar is fully filled it will be removed from the screen automatically.
		Note: Set Duration to 0 to hide the bar.
	*/
	BEGIN_READ(pbuf, iSize);
	int Duration = READ_SHORT();

	return oBarTime(pszName, iSize, pbuf);
}

int Hooked_RoundTime(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message updates the round timer on the HUD. Time is in seconds.
	BEGIN_READ(pbuf, iSize);
	int Time = READ_SHORT();

	return oRoundTime(pszName, iSize, pbuf);
}

int Hooked_BlinkAcct(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message makes a player's money display flash rapidly, a total of BlinkAmt times.
	BEGIN_READ(pbuf, iSize);
	int BlinkAmt = READ_BYTE();

	return oBlinkAcct(pszName, iSize, pbuf);
}

int Hooked_Money(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message updates the amount of money on the HUD. If the Flag is 1, the amount of money added will also be displayed.
	BEGIN_READ(pbuf, iSize);
	int Amount = READ_LONG();
	int Flag = READ_BYTE();

	return oMoney(pszName, iSize, pbuf);
}

int Hooked_StatusIcon(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Half-Life: Opposing Force • Team Fortress Classic
	// This message draws/removes the specified status HUD icon. For Status, 0 is Hide Icon, 1 is Show Icon, 2 is Flash Icon. Color arguments are optional and are required only if Status isn't equal to 0.
	BEGIN_READ(pbuf, iSize);
	int Status = READ_BYTE();
	char* SpriteName = READ_STRING();
	int ColorR = READ_BYTE();
	int ColorG = READ_BYTE();
	int ColorB = READ_BYTE();

	return oStatusIcon(pszName, iSize, pbuf);
}

int Hooked_TextMsg(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message prints a custom or predefined text message.
		There does not necessarily have to be a total of 6 arguments; there could be as little as 2. For example, you can send a message with the following:

		Arg1: 1
		Arg2: #Game_join_ct
		Arg3: Pimp Daddy
	*/
	BEGIN_READ(pbuf, iSize);
	int DestinationType = READ_BYTE();
	char* Message = READ_STRING();
	char* Submsg1 = READ_STRING();
	char* Submsg2 = READ_STRING();
	char* Submsg3 = READ_STRING();
	char* Submsg4 = READ_STRING();

	return oTextMsg(pszName, iSize, pbuf);
}

int Hooked_SecAmmoIcon(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Team Fortress Classic • Half-Life Deathmatch • Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message creates an icon at the bottom right corner of the screen. TFC uses it to display carried grenade icon. It is not registered in other mods, but it is still useable though.

		Note: icon is any sprite name from hud.txt.
		Note: this message will have effect only when sent in conjuction with SecAmmoVal message.
	*/
	BEGIN_READ(pbuf, iSize);
	char* Icon = READ_STRING();

	return oSecAmmoIcon(pszName, iSize, pbuf);
}

int Hooked_SecAmmoVal(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Team Fortress Classic • Half-Life Deathmatch • Counter-Strike • Counter-Strike: Condition Zero
	/*
		It is used to show carried grenade amount in TFC; it is disabled on all other mods, but it is still useable though.

		Note: Slots range from 1 to 4.
		Note: Sending 0 as amount for all slots will remove the effect of this message.
	*/
	BEGIN_READ(pbuf, iSize);
	int Slot = READ_BYTE();
	int Amount = READ_BYTE();

	return oSecAmmoVal(pszName, iSize, pbuf);
}

int Hooked_DeathMsg(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This event is fired to all players (MSG_ALL or MSG_BROADCAST) to notify them of a death. This generates the HUD message the client sees in the upper right corner of their screen.
		It also prints the console text message "KillerName killed VictimName with TruncatedWeaponName" or "*** KillerName killed VictimName with a headshot from TruncatedWeaponName ***"

		Note: This message has different parameters depending upon the mod.
		Note: KillerID may not always be a Player ID. It would be 0 if a player died from fall/acid/radiation/fire/etc damage/lack of oxygen or from touch to a "trigger_hurt" entity,
		      in which cases TruncatedWeaponName will be "worldspawn" and "trigger_hurt" respectively.
		Note: For vehicle kills, TruncatedWeaponName could be "vehicle", "tank", etc.
		Note: In some mods, TruncatedWeaponName is "teammate" for a team kill, which shows a green skull in the HUD message.

		Counter-Strike:
		Note: TruncatedWeaponName doesn't contain a "weapon_" prefix. See CS Weapons Information for more information.
		Note: For a grenade kill, TruncatedWeaponName isn't "hegrenade", but rather "grenade", which is the actual classname of a thrown grenade.
	*/
	BEGIN_READ(pbuf, iSize);
	int KillerID = READ_BYTE();
	int VictimID = READ_BYTE();
	int IsHeadshot = READ_BYTE();
	char* TruncatedWeaponName = READ_STRING();

	return oDeathMsg(pszName, iSize, pbuf);
}

int Hooked_StatusValue(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Natural Selection • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message sends/updates the status values. For Flag, 1 is TeamRelation, 2 is PlayerID, and 3 is Health. For TeamRelation, 1 is Teammate player, 2 is Non-Teammate player, 3 is Hostage. If TeamRelation is Hostage, PlayerID will be 0 or will be not sent at all.
		Usually this is fired as a triple message, for example:

		{1,  2}  -  non-teammate player
		{2, 17}  -  player index is 17
		{3, 59}  -  player health is 59
	*/
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();
	int Value = READ_SHORT();

	return oStatusValue(pszName, iSize, pbuf);
}

int Hooked_StatusText(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Natural Selection • Team Fortress Classic • Half-Life Deathmatch
	// This message specifies the status text format.
	BEGIN_READ(pbuf, iSize);
	int Unknown = READ_BYTE();
	char* Text = READ_STRING();

	return oStatusText(pszName, iSize, pbuf);
}

int Hooked_GameTitle(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// Note: No Information is available for this message.
	BEGIN_READ(pbuf, iSize);
	int Unknown = READ_BYTE();

	return oGameTitle(pszName, iSize, pbuf);
}

int Hooked_HudTextArgs(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message prints HUD text.
		Note: An example of TextCode could be "#Hint_you_have_the_bomb".
		Note: Prints message with specified style in titles.txt with Big signs (CS Default)
		Note: If you have problems specifying the last two arguments, use 1 and 0 respectively.
	*/
	BEGIN_READ(pbuf, iSize);
	char* TextCode = READ_STRING();
	int InitHUDstyle = READ_BYTE();
	int NumberOfSubMessages = READ_BYTE();
	//char* SubMsg1 = READ_STRING();

	return oHudTextArgs(pszName, iSize, pbuf);
}

int Hooked_HudTextPro(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message prints HUD text.
		Note: Prints message with specified style in titles.txt with Big signs (CS Default)
	*/
	BEGIN_READ(pbuf, iSize);
	char* TextCode = READ_STRING();
	int InitHUDstyle = READ_BYTE();

	return oHudTextPro(pszName, iSize, pbuf);
}

int Hooked_HudText(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message prints HUD text.
		Note: Prints message with specified style in titles.txt with small signs (like in HL)
	*/
	BEGIN_READ(pbuf, iSize);
	char* TextCode = READ_STRING();
	int InitHUDstyle = READ_BYTE();

	return oHudText(pszName, iSize, pbuf);
}

int Hooked_FlashBat(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message updates the flashlight battery charge on the HUD.
	BEGIN_READ(pbuf, iSize);
	int ChargePercentage = READ_BYTE();

	return oFlashBat(pszName, iSize, pbuf);
}

int Hooked_Flashlight(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message updates the flashlight state and battery charge on the HUD. If Flag is set to 1 the flashlight HUD icon will be shown as active.
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();
	int ChargePercent = READ_BYTE();

	return oFlashlight(pszName, iSize, pbuf);
}

int Hooked_ArmorType(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods : Counter - Strike • Counter - Strike : Condition Zero
	/*
		This message draws/removes the helmet HUD icon. If flag is set to 1, the helmet HUD icon will be drawn (located right on the armor icon).
		Note: See CS Weapons Information for more information. (https://wiki.alliedmods.net/CS_Weapons_Information)
	*/
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();

	return oArmorType(pszName, iSize, pbuf);
}

int Hooked_Battery(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message updates the icon and numerical armor value on the HUD.
	BEGIN_READ(pbuf, iSize);
	int Armor = READ_SHORT();

	return oBattery(pszName, iSize, pbuf);
}

int Hooked_Train(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message displays the speed bar used for controlling a train.
		Note: Speed is as follows: 0 (disable display), 1 (neutral), 2 (slow speed), 3 (medium speed), 4 (maximum speed), 5 (reverse)
	*/
	BEGIN_READ(pbuf, iSize);
	int Speed = READ_BYTE();

	return oTrain(pszName, iSize, pbuf);
}

int Hooked_Geiger(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message signals the client to notify the player of the radiation level through special sound signals. Distance is the distance to the hazard area.
	BEGIN_READ(pbuf, iSize);
	int Distance = READ_BYTE();

	return oGeiger(pszName, iSize, pbuf);
}

int Hooked_SendAudio(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message plays the specified audio. An example of AudioCode could be "%!MRAD_rounddraw".
	int SenderID = READ_BYTE();
	char* AudioCode = READ_STRING();
	int Pitch = READ_SHORT();

	return oSendAudio(pszName, iSize, pbuf);
}

int Hooked_SayText(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message prints say HUD text. The second argument can be a predefined string or a custom one. In the latter case, the last two arguments aren't required.
		Examples of predefined Counter-Strike string values include #Cstrike_Chat_AllDead and #Cstrike_Name_Change.
		Note: For #Cstrike_Name_Change String2 is an old name and String3 is a new name.
	*/
	BEGIN_READ(pbuf, iSize);
	int SenderID = READ_BYTE();
	char* String1 = READ_STRING();
	char* String2 = READ_STRING();
	char* String3 = READ_STRING();

	return oSayText(pszName, iSize, pbuf);
}

int Hooked_ReceiveW(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message tells the client which visual weather effect to be executed client side, if client's cl_weather CVar is above 0.
		Note: Main part of CBasePlayer::SendWeatherInfo() function that is sent in CBasePlayer :: UpdateClientData() when player offset m_fInitHUD is 1
			  (right after putinserver or after fullupdate command)
			  Mode: 1 is for rain effect, 2 is for snow effect
			  Though mode 0 is never sent by the game itself, it removes the weather effect.
			  Alternatively send mode 1 and mode 2 with judicious delays (time for effect to disappear) to make both rain and snow effect
	*/
	BEGIN_READ(pbuf, iSize);
	int Mode = READ_BYTE();
	return oReceiveW(pszName, iSize, pbuf);
}

int Hooked_ClCorpse(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat
	/*
		This message spawns a player's corpse. ModelName is the player's model name, for example: "leet". Delay is a delay before animation playback, which can be a negative value.
		Note: Coord and Delay is multiplied by 128.
		Note: In CS, argument #10 is always equal to 0.
		See CS Team Constants for team indices constants list. (http://www.amxmodx.org/funcwiki.php?go=module&id=4#const_teams)
	*/
	BEGIN_READ(pbuf, iSize);
	char* ModelName = READ_STRING();
	int CoordX = READ_LONG();
	int CoordY = READ_LONG();
	int CoordZ = READ_LONG();
	float AngleX = READ_COORD();
	float AngleY = READ_COORD();
	float AngleZ = READ_COORD();
	int Delay = READ_LONG();
	int Sequence = READ_BYTE();
	int ClassID = READ_BYTE();
	int TeamID = READ_BYTE();
	int PlayerID = READ_BYTE();

	return oClCorpse(pszName, iSize, pbuf);
}

int Hooked_ScoreAttrib(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message updates the scoreboard attribute for the specified player. For the 2nd argument, 0 is nothing, (1<<0) i.e. 1 is dead, (1<<1) i.e. 2 is bomb, (1<<2) i.e. 4 is VIP.
		Note: Flags is a bitwise value so if VIP player is dying with the bomb the Flags will be 7 i.e. bit sum of all flags.
	*/
	BEGIN_READ(pbuf, iSize);
	int PlayerID = READ_BYTE();
	int Flags = READ_BYTE();

	return oScoreAttrib(pszName, iSize, pbuf);
}

int Hooked_Radar(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message draws/updates the dot on the HUD radar which indicates the given player position.
		Note: This works for teammates only.
	*/
	BEGIN_READ(pbuf, iSize);
	int PlayerID = READ_BYTE();
	float CoordX = READ_COORD();
	float CoordY = READ_COORD();
	float CoordZ = READ_COORD();

	return oRadar(pszName, iSize, pbuf);
}

int Hooked_Damage(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message is sent when a player takes damage, to display the red locational indicators.
		The last three arguments are the origin of the damage inflicter or victim origin if inflicter isn't found. DamageType is a bitwise value which usually consists of a single bit.
		Note: To capture this message, you should use "b" as the third parameter in the register_event() function.
	*/
	BEGIN_READ(pbuf, iSize);
	int DamageSave = READ_BYTE();
	int DamageTake = READ_BYTE();
	int DamageType = READ_LONG();
	float CoordX = READ_COORD();
	float CoordY = READ_COORD();
	float CoordZ = READ_COORD();

	return oDamage(pszName, iSize, pbuf);
}

int Hooked_Health(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message updates the numerical health value on the HUD.
	BEGIN_READ(pbuf, iSize);
	int Health = READ_BYTE();

	return oHealth(pszName, iSize, pbuf);
}

int Hooked_Crosshair(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods : Counter - Strike • Counter - Strike : Condition Zero
	/*
		This message draws/removes a crosshair. If Flag is set to 1 the crosshair will be drawn.
		Note: This crosshair looks not like the regular one, but like the one that is drawn in spectator mode.
	*/
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();

	return oCrosshair(pszName, iSize, pbuf);
}

int Hooked_AmmoX(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// Note: See CS Weapons Information for more information. (https://wiki.alliedmods.net/CS_Weapons_Information)
	BEGIN_READ(pbuf, iSize);
	int AmmoID = READ_BYTE();
	int Ammount = READ_BYTE();

	return oAmmoX(pszName, iSize, pbuf);
}

int Hooked_HideWeapon(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message hides the specified HUD elements.
		Flags:

		  1   (1<<0)  -  crosshair, ammo, weapons list
		  2   (1<<1)  -  flashlight, +
		  4   (1<<2)  -  ALL
		  8   (1<<3)  -  radar, health, armor, +
		 16   (1<<4)  -  timer, +
		 32   (1<<5)  -  money, +
		 64   (1<<6)  -  crosshair
		128   (1<<7)  -  +
	*/
	BEGIN_READ(pbuf, iSize);
	int Flags = READ_BYTE();

	return oHideWeapon(pszName, iSize, pbuf);
}

int Hooked_ItemPickup(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message temporarily draws a corresponding item HUD icon in the middle of the right side of the screen.
		Note: Draw time is dependent on the hud_drawhistory_time client CVar value.
	*/
	BEGIN_READ(pbuf, iSize);
	char* ItemName = READ_STRING();

	return oItemPickup(pszName, iSize, pbuf);
}

int Hooked_WeapPickup(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message temporarily draws the corresponding weapon HUD icon in the middle of the right side of the screen.
		Note: Draw time depends on the hud_drawhistory_time client CVar value.
		Note: This is fired right before weapon is picked up (notice "before").
		Note: See CS Weapons Information for more information. (https://wiki.alliedmods.net/CS_Weapons_Information)
	*/
	BEGIN_READ(pbuf, iSize);
	int WeaponID = READ_BYTE();

	return oWeapPickup(pszName, iSize, pbuf);
}

int Hooked_AmmoPickup(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message temporarily draws HUD numerical ammo amount and corresponding ammo HUD icon in the middle of the right side of the screen.
		Note: Draw time depends on the hud_drawhistory_time client CVar value.
		Note: See CS Weapons Information for more information. (https://wiki.alliedmods.net/CS_Weapons_Information)
	*/
	BEGIN_READ(pbuf, iSize);
	int AmmoID = READ_BYTE();
	int Ammount = READ_BYTE();

	return oAmmoPickup(pszName, iSize, pbuf);
}

int Hooked_WeaponList(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message configures the HUD weapons list.
		Note: This is fired on map initialization.
		Note: SlotID starts from 0.
		Flags (from HLSDK):

		ITEM_FLAG_SELECTONEMPTY       1
		ITEM_FLAG_NOAUTORELOAD        2
		ITEM_FLAG_NOAUTOSWITCHEMPTY   4
		ITEM_FLAG_LIMITINWORLD        8
		ITEM_FLAG_EXHAUSTIBLE        16 // A player can totally exhaust their ammo supply and lose this weapon.
		Note: See CS Weapons Information for more information. (https://wiki.alliedmods.net/CS_Weapons_Information)
	*/
	BEGIN_READ(pbuf, iSize);
	char* WeaponName = READ_STRING();
	int PrimaryAmmoID = READ_BYTE();
	int PrimaryAmmoMaxAmount = READ_BYTE();
	int SecondaryAmmoID = READ_BYTE();
	int SecondaryAmmoMaxAmount = READ_BYTE();
	int SlotID = READ_BYTE();
	int NumberInSlot = READ_BYTE();
	int WeaponID = READ_BYTE();
	int Flags = READ_BYTE();

	return oWeaponList(pszName, iSize, pbuf);
}

int Hooked_CurWeapon(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message updates the numerical magazine ammo count and the corresponding ammo type icon on the HUD.
		Note: See CS Weapons Information for more information on Counter-Strike weapons. (https://wiki.alliedmods.net/CS_Weapons_Information)
	*/
	BEGIN_READ(pbuf, iSize);
	int IsActive = READ_BYTE();
	int WeaponID = READ_BYTE();
	int ClipAmmo = READ_BYTE();

	return oCurWeapon(pszName, iSize, pbuf);
}

int Hooked_NVGToggle(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message toggles night vision mode. For Flag: 1 is on, 0 is off.
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();

	return oNVGToggle(pszName, iSize, pbuf);
}

int Hooked_ItemStatus(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message notifies the client about carried items.
		Example of some item bits:

		1   (1<<0)  -  nightvision goggles
		2   (1<<1)  -  defusal kit
	*/
	BEGIN_READ(pbuf, iSize);
	int ItemsBitSum = READ_BYTE();

	return oItemStatus(pszName, iSize, pbuf);
}

int Hooked_BotProgress(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message is sent when CZ's bots are learning a new map. It displays a progress bar in the middle of the screen, with some header text.
		The bar doesn't move, and you can't do anything while the bar is displayed. This is a different style of progress bar than from the BarTime event. This really doesn't display well in CS.
		Note: Flag can be 0 (update bar), 1 (create new bar), or 2 (remove bar). When using flag 0, send all arguments. When using flag 1, send only Flag and Header. When using flag 2, send only Flag.
	*/
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();
	int Progress = READ_BYTE();
	char* Header = READ_STRING();

	return oBotProgress(pszName, iSize, pbuf);
}

int Hooked_SpecHealth2(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message updates a spectator's screen with the name and health of the given player when player is freshly spectated.
	BEGIN_READ(pbuf, iSize);
	int Health = READ_BYTE();
	int PlayerID = READ_BYTE();

	return oSpecHealth2(pszName, iSize, pbuf);
}

int Hooked_BuyClose(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message forces the buy menu to close. This is not called when the player manually closes the buy menu; it's only called when the game forces them to do so
		(e.g. walking outside of the buy zone, getting killed, etcetera).
		Note: This message has no arguments.
	*/
	return oBuyClose(pszName, iSize, pbuf);
}

int Hooked_TutorClose(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message closes all CZ-style tutor popups.
		Note: This message has no arguments.
	*/
	return oTutorClose(pszName, iSize, pbuf);
}

int Hooked_TutorState(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// Note: No Information is available for this message.
	char* Unknown = READ_STRING();

	return oTutorState(pszName, iSize, pbuf);
}

int Hooked_TutorLine(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// Note: No Information is available for this message.
	BEGIN_READ(pbuf, iSize);
	int Unknown1 = READ_SHORT();
	int Unknown2 = READ_SHORT();

	return oTutorLine(pszName, iSize, pbuf);
}

int Hooked_TutorText(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message is used to display a CZ-style tutor popup.
		Note: If NumberOfSubMsgs is higher than 0, there should be such amount of write_string after this byte.
		Note: TutorMessageEventId is indexed as listed in czero/tutordata.txt and starts from 0
		Note: IsDead is the message receiver alive status
		DEFAULT		1	// 1<<0 | GREEN  | INFO
		FRIENDDEATH	2	// 1<<1 | RED    | SKULL
		ENEMYDEATH	4	// 1<<2 | BLUE   | SKULL
		SCENARIO	8	// 1<<3 | YELLOW | INFO
		BUY		16	// 1<<4 | GREEN  | INFO
		CAREER		32	// 1<<5 | GREEN  | INFO
		HINT		64	// 1<<6 | GREEN  | INFO
		INGAMEHINT	128	// 1<<7 | GREEN  | INFO
		ENDGAME		256	// 1<<8 | YELLOW | INFO
	*/
	BEGIN_READ(pbuf, iSize);
	char* String = READ_STRING();
	int NumberOfSubMsgs = READ_BYTE();
	for (int i = 0; i < NumberOfSubMsgs; ++i)
		char* SubMessage = READ_STRING();

	int TutorMessageEventId = READ_SHORT();
	int IsDead = READ_SHORT();
	int Type = READ_SHORT();

	return oTutorText(pszName, iSize, pbuf);
}

int Hooked_VGUIMenu(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Half-Life: Opposing Force • Sven Co-op • Team Fortress Classic
	// This message displays a predefined VGUI menu.
	BEGIN_READ(pbuf, iSize);
	int MenuID = READ_BYTE();
	int KeysBitSum = READ_SHORT();
	int Time = READ_CHAR();
	int Multipart = READ_BYTE();
	char* Name = READ_STRING();

	return oVGUIMenu(pszName, iSize, pbuf);
}

int Hooked_ForceCam(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message is sent whenever mp_forcecam or mp_forcechasecam are changed, with their new values passed.
		There is presumably a third CVar that this tracks, but which one is currently unknown. Note that this message doesn't actually change any of the spectating rules for the client.
		Note: Even if mp_forcechasecam is set to 2, it is sent by this message as 1.
	*/
	BEGIN_READ(pbuf, iSize);
	int ForcecamValue = READ_BYTE();
	int ForcechasecamValue = READ_BYTE();
	int Unknown = READ_BYTE();

	return oForceCam(pszName, iSize, pbuf);
}

int Hooked_AllowSpec(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Half-Life: Opposing Force • Team Fortress Classic
	/*
		This message changes whether or not "SPECTATE" appears on the change team menu. It is sent whenever the allow_spectators CVar is changed, with its new value sent as the byte.
		Note: This changes how the change team menu appears, but spectating functionality is based on the actual CVar value
	*/
	BEGIN_READ(pbuf, iSize);
	int Allowed = READ_BYTE();

	return oAllowSpec(pszName, iSize, pbuf);
}

int Hooked_Spectator(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Half-Life: Opposing Force • Ricochet • Sven Co-op • Team Fortress Classic
	/*
		This message is sent when a player becomes an observer/spectator.
		Note: On join to Spectators this usually is fired twice in a row.
	*/
	BEGIN_READ(pbuf, iSize);
	int ClientID = READ_BYTE();
	int Unknown = READ_BYTE();

	return oSpectator(pszName, iSize, pbuf);
}

int Hooked_Location(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message is sent when a player changes zones on a map.
	BEGIN_READ(pbuf, iSize);
	int PlayerId = READ_BYTE();
	char* LocationName = READ_STRING();

	return oLocation(pszName, iSize, pbuf);
}

int Hooked_TeamInfo(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message sets the team information for the given player.
		Note: In CS TeamName is either "UNASSIGNED", "TERRORIST", "CT" or "SPECTATOR".
	*/
	BEGIN_READ(pbuf, iSize);
	int PlayerID = READ_BYTE();
	char* TeamName = READ_STRING();

	return oTeamInfo(pszName, iSize, pbuf);
}

int Hooked_TeamScore(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message updates the team score on the scoreboard.
		Note: This message has different parameters depending upon the mod.
		Note: In CS TeamName is either "TERRORIST" or "CT".
	*/
	BEGIN_READ(pbuf, iSize);
	char* TeamName = READ_STRING();
	int Score = READ_SHORT();

	return oTeamScore(pszName, iSize, pbuf);
}

int Hooked_ScoreInfo(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message updates the scoreboard with the given player's Score and Deaths. In Counter-Strike, the score is based on the number of frags and the bomb detonating or being defused. In Team Fortress Classic, the score is based on the number of kills, suicides, and captures. Day of Defeat uses ScoreShort and ObjScore instead of this message to update score and deaths.
		Note: In CS the 4th argument (ClassID) is always equal to 0.
		See CS Team Constants for team indices constants list. (http://www.amxmodx.org/funcwiki.php?go=module&id=4#const_teams)
	*/
	BEGIN_READ(pbuf, iSize);
	int PlayerID = READ_BYTE();
	int Score = READ_SHORT();
	int Deaths = READ_SHORT();
	int ClassID = READ_SHORT();
	int TeamID = READ_SHORT();

	return oScoreInfo(pszName, iSize, pbuf);
}

int Hooked_ServerName(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message sends the server name to a client.
	BEGIN_READ(pbuf, iSize);
	char* ServerName = READ_STRING();
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
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message displays the MOTD window.
		Note: Max. Text length is 60. A larger MOTD is sent in multiple messages. Flag will be set to 1 for the final segment.
	*/
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();
	char* Text = READ_STRING();

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
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message forces the round timer to display.
		Note: This message has no arguments.
	*/
	return oShowTimer(pszName, iSize, pbuf);
}

int Hooked_Fog(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Natural Selection • Sven Co-op
	// Note: mp_Fog 1 for fog in Counter-Strike
	BEGIN_READ(pbuf, iSize);
	int FogValue = READ_BYTE();
	int FogValue2 = READ_BYTE();
	int Unknown = READ_BYTE();

	return oFog(pszName, iSize, pbuf);
}

int Hooked_Brass(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message creates a brass shell. Used, for example, by the AWP, after firing.
	BEGIN_READ(pbuf, iSize);
	int MessageID = READ_BYTE();
	float StartX = READ_COORD();
	float StartY = READ_COORD();
	float StartZ = READ_COORD();
	float VelocityX = READ_COORD();
	float VelocityY = READ_COORD();
	float VelocityZ = READ_COORD();
	float UnknownX = READ_COORD();
	float UnknownY = READ_COORD();
	float UnknownZ = READ_COORD();
	float Angle = READ_ANGLE();
	int ModelIndex = READ_SHORT();
	int BounceSoundType = READ_BYTE();
	int Life = READ_BYTE();
	int PlayerID = READ_BYTE();

	return oBrass(pszName, iSize, pbuf);
}

int Hooked_BotVoice(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message displays (or hides) the voice icon above a user's head and the talking icon on the right side of the screen.
		This is called by CZ for bots; it's not called for regular players, although you can specify a regular player (non-bot) for the PlayerIndex. Status is 1 for talking, or 0 for not talking.
	*/
	BEGIN_READ(pbuf, iSize);
	int Status = READ_BYTE();
	int PlayerIndex = READ_BYTE();

	return oBotVoice(pszName, iSize, pbuf);
}

int Hooked_ShadowIdx(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		Note: Creates/Hides shadow beneath player.
		Note: Passing 0 as the argument will hide the shadow.
	*/
	BEGIN_READ(pbuf, iSize);
	int spriteIndex = READ_LONG();

	return oShadowIdx(pszName, iSize, pbuf);
}

int Hooked_CZCareerHUD(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message displays certain HUD elements regarding Condition Zero single-player missions. (https://wiki.alliedmods.net/HUD)
		Note: See the CZCareerHUD page for more information.
		Note: Using an invalid type has no repercussions whatsoever. Therefore, you can use this to make your own custom communications (you can send any number of arguments of any type after the first string).
		Note: The Type argument is case-sensitive.
		Note: This event has some limited functionality in CS and CZ multi-player (albeit better in CZ).
	*/
	BEGIN_READ(pbuf, iSize);
	char* Type = READ_STRING();
	return oCZCareerHUD(pszName, iSize, pbuf);
}

int Hooked_HostageK(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	// This message temporarily draws a blinking red dot on the CT players' radar when a hostage is killed.
	BEGIN_READ(pbuf, iSize);
	int HostageID = READ_BYTE();

	return oHostageK(pszName, iSize, pbuf);
}

int Hooked_HostagePos(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message draws/updates the blue mark on the CT players' radar which indicates the corresponding hostage's position.
		Note: It is called with Flag set to 1 on player HUD full update.
	*/
	BEGIN_READ(pbuf, iSize);
	int Flag = READ_BYTE();
	int HostageID = READ_BYTE();
	float CoordX = READ_COORD();
	float CoordY = READ_COORD();
	float CoordZ = READ_COORD();

	return oHostagePos(pszName, iSize, pbuf);
}

int Hooked_ADStop(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		Note: No Information is available for this message.
		Note: This message has no arguments.
	*/

	return oADStop(pszName, iSize, pbuf);
}

int Hooked_BombPickup(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message just tells the clients that the bomb has been picked up. It will cause the dropped bomb to disappear from the Terrorist team's radar.
		Note: This message has no arguments.
	*/
	return oBombPickup(pszName, iSize, pbuf);
}

int Hooked_BombDrop(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods : Counter - Strike • Counter - Strike : Condition Zero
	/*
		This message is sent when the bomb is dropped or planted by a player.
		The first three arguments are the origin of the dropped bomb.
		The last argument is set to 0 if the bomb was dropped due to voluntary dropping or death / disconnect.
		It is set to 1 if the bomb was planted, which will trigger the round timer to hide.
		It also will show the dropped bomb on the Terrorist team's radar in the location specified by the first three arguments.
	*/
	BEGIN_READ(pbuf, iSize);
	float CoordX = READ_COORD();
	float CoordY = READ_COORD();
	float CoordZ = READ_COORD();
	int Flag = READ_BYTE();

	return oBombDrop(pszName, iSize, pbuf);
}

int Hooked_ReloadSound(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message plays generic reload sounds.
		Note: Setting IsNotShotgun to 1 will play weapons/generic_reload.wav
		Note: Setting IsNotShotgun to 0 will play weapons/generic_shot_reload.wav
	*/
	BEGIN_READ(pbuf, iSize);
	int Volume = READ_BYTE(); // *255
	int IsNotShotgun = READ_BYTE();

	return oReloadSound(pszName, iSize, pbuf);
}

int Hooked_Concuss(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Team Fortress Classic • Half-Life Deathmatch • Counter-Strike • Counter-Strike: Condition Zero
	/*
		This message creates screen shake effect similar to the TFC concussion grenade effect.
		Note: In all mods except TFC, this message requires to be registered by using EngFunc_RegUserMsg.
	*/
	BEGIN_READ(pbuf, iSize);
	int Amount = READ_BYTE();

	return oConcuss(pszName, iSize, pbuf);
}

int Hooked_SpecHealth(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Team Fortress Classic
	/*
		This message updates a spectator's screen with health of the currently spectated player, on health change (on TakeDamage, doesn't seems to be sent anywhere else).
		Note: Previous information has been checked on cs1.6/cz only
	*/
	BEGIN_READ(pbuf, iSize);
	int Health = READ_BYTE();

	return oSpecHealth(pszName, iSize, pbuf);
}

int Hooked_HLTV(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat
	/*
		This message is sent for HLTV and is unique for each round-start.
		On new round is fired 2 messages:

		// reset all players health for HLTV
		MESSAGE_BEGIN( MSG_SPEC, gmsgHLTV );
		WRITE_BYTE( 0 );   // 0 = all players
		WRITE_BYTE( 100 | 128 );
		MESSAGE_END();

		// reset all players FOV for HLTV
		MESSAGE_BEGIN( MSG_SPEC, gmsgHLTV );
		WRITE_BYTE( 0 );   // all players
		WRITE_BYTE( 0 );
		MESSAGE_END();
	*/
	BEGIN_READ(pbuf, iSize);
	int ClientID = READ_BYTE();
	int Flags = READ_BYTE();

	return oHLTV(pszName, iSize, pbuf);
}

int Hooked_SetFOV(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message sets the specified field of view.
	BEGIN_READ(pbuf, iSize);
	int Degrees = READ_BYTE();

	return oSetFOV(pszName, iSize, pbuf);
}

int Hooked_ViewMode(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Team Fortress Classic
	/*
		Note: No Information is available for this message (HLSDK says this switches to first-person view, but it doesn't seem to function as so).
		Note: This message has no arguments.
	*/
	return oViewMode(pszName, iSize, pbuf);
}

int Hooked_InitHUD(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message initializes the HUD.
		Note: This message has no arguments.
	*/
	return oInitHUD(pszName, iSize, pbuf);
}

int Hooked_GameMode(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Deathmatch Classic • Half-Life: Opposing Force • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	// This message informs the client of the current game mode.
	BEGIN_READ(pbuf, iSize);
	int GameMode = READ_BYTE();

	return oGameMode(pszName, iSize, pbuf);
}

int Hooked_ResetHUD(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message resets the HUD.
		Note: This message has no arguments.
	*/

	AtRoundStart();
	return oResetHUD(pszName, iSize, pbuf);
}

int Hooked_Logo(const char *pszName, int iSize, void *pbuf)
{
	return oLogo(pszName, iSize, pbuf);
}

int Hooked_ScreenFade(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message fades the screen.
		Note: Duration and HoldTime is in special units. 1 second is equal to (1<<12) i.e. 4096 units.
			  Flags (from HLSDK):

		FFADE_IN         0x0000 // Just here so we don't pass 0 into the function
		FFADE_OUT        0x0001 // Fade out (not in)
		FFADE_MODULATE   0x0002 // Modulate (don't blend)
		FFADE_STAYOUT    0x0004 // ignores the duration, stays faded out until new ScreenFade message received
	*/
	BEGIN_READ(pbuf, iSize);
	int Duration = READ_SHORT();
	int HoldTime = READ_SHORT();
	int Flags = READ_SHORT();
	int ColorR = READ_BYTE();
	int ColorG = READ_BYTE();
	int ColorB = READ_BYTE();
	int Alpha = READ_BYTE();

	return oScreenFade(pszName, iSize, pbuf);
}

int Hooked_ScreenShake(const char *pszName, int iSize, void *pbuf)
{
	// Supported Mods:	Counter-Strike • Counter-Strike: Condition Zero • Day of Defeat • Deathmatch Classic • Half-Life: Opposing Force • Natural Selection • Ricochet • Sven Co-op • Team Fortress Classic • Half-Life Deathmatch
	/*
		This message shakes the screen.
		Note: All arguments is in special units. 1 second is equal to (1<<12) i.e. 4096 units.
	*/
	BEGIN_READ(pbuf, iSize);
	int Amplitude = READ_SHORT();
	int Duration = READ_SHORT();
	int Frequency = READ_SHORT();

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