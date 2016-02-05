// ===================================================================================
// Externals
extern engine_studio_api_t* g_pStudio;
extern engine_studio_api_t g_oStudio;
// ===================================================================================


// ===================================================================================
// Studio helper
namespace StudioHelper
{
	mstudioseqdesc_t* GetSequenceDescription(int PlayerID, int Sequence);
	mstudiobone_t* GetStudioBone(int PlayerID, int BoneID);
	void GetPlayerBone(int PlayerID, int BoneID, float* Out);
	bool IsVisible(int PlayerID);
}
// ===================================================================================


// ===================================================================================
// Studio table hook
void HookStudioTable();
void UnhookStudioTable();
// ===================================================================================