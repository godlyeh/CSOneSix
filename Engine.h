// ===================================================================================
// Externals
extern cl_enginefunc_t* g_pEngine;
extern cl_enginefunc_t g_oEngine;
extern net_api_t* g_pNetApi;
extern client_sprite_t* g_pSpriteList;
extern HSPRITE* g_pSprite;
// ===================================================================================


// ===================================================================================
// Engine helper
namespace EngineHelper
{
	static net_status_t NetStatus;
	static DWORD dwHUDPointer = 0;

	static bool IsConnected()
	{
		g_pNetApi->Status(&NetStatus);
		return (NetStatus.connected != 0);
	}

	static void InitHUD()
	{
		g_pNetApi = g_pEngine->pNetAPI;
		dwHUDPointer = Utility->FindPattern("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 85 C0 74 59");
		g_pSpriteList = *(client_sprite_t**)(dwHUDPointer + 0xC); // HUD->m_pSpriteList
		g_pSprite = *(HSPRITE**)(dwHUDPointer + 0x178); // HUD->m_rghSprites

		Utility->DeleteLog("HUD.txt");
		Utility->Log("HUD.txt", "HUD Pointer: 0x%p\n", dwHUDPointer);

		Utility->Log("HUD.txt", "HUD Sprite List: 0x%p\n", g_pSpriteList);
	}

	static void Initialize()
	{
		InitHUD();
	}

}
// ===================================================================================


// ===================================================================================
// Engine table hook
void HookEngineTable();
void UnhookEngineTable();
// ===================================================================================