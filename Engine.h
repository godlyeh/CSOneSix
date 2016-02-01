// ===================================================================================
// Externals
typedef float ViewMatrix[4];

extern cl_enginefunc_t* g_pEngine;
extern cl_enginefunc_t g_oEngine;
extern net_api_t* g_pNetApi;
extern client_sprite_t* g_pSpriteList;
extern SCREENINFO g_ScreenInfo;
extern HSPRITE* g_pSprite;
extern ViewMatrix* g_pViewMatrix;
// ===================================================================================


// ===================================================================================
// Engine helper
namespace EngineHelper
{
	static net_status_t NetStatus;
	static DWORD dwHUDPointer = 0;

	// Client info
	bool IsConnected();
	void UpdateScreenInfo();
	bool ValidEntity(int EntityID);
	bool ValidPlayer(int PlayerID);

	// Engine math
	bool WorldToScreen(float* Origin, float* Out);

	// Init
	void InitHUD();
	void Initialize();
}
// ===================================================================================


// ===================================================================================
// Engine table hook
void HookEngineTable();
void UnhookEngineTable();
// ===================================================================================


// ===================================================================================
// Vector math helpers
#define POW(x)						((x) * (x))
#define VectorDistance(a, b)		(float)(sqrt(POW(a[0]-b[0]) + POW(a[1]-b[1]) + POW(a[2]-b[2])))
// ===================================================================================