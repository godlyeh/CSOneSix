// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
engine_studio_api_t* g_pStudio;
engine_studio_api_t g_oStudio;
// ===================================================================================


// ===================================================================================
// Studio helper
mstudioseqdesc_t* StudioHelper::GetSequenceDescription(int PlayerID, int Sequence)
{
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(PlayerID);
	if (pEntity == NULL) return NULL;
	studiohdr_t* pStudioHdr = (studiohdr_t*)g_oStudio.Mod_Extradata(pEntity->model);
	if (!pStudioHdr) return NULL;
	return &((mstudioseqdesc_t*)((byte*)pStudioHdr + pStudioHdr->seqindex))[Sequence];
}

mstudiobone_t* StudioHelper::GetStudioBone(int PlayerID, int BoneID)
{
	model_t* pModel = g_oStudio.SetupPlayerModel(PlayerID);
	if (pModel == NULL) return NULL;
	studiohdr_t* pStudioHdr = (studiohdr_t*)g_oStudio.Mod_Extradata(pModel);
	if (!pStudioHdr) return NULL;
	return &((mstudiobone_t*)((byte*)pStudioHdr + pStudioHdr->boneindex))[BoneID];
}

void StudioHelper::GetPlayerBone(int PlayerID, int BoneGroup, int BoneID, float* Out)
{
	Vector vBone;

	if (BoneGroup)
	{
		vBone[0] = g_Player[PlayerID].BoneMatrix2[BoneID][0][3];
		vBone[1] = g_Player[PlayerID].BoneMatrix2[BoneID][1][3];
		vBone[2] = g_Player[PlayerID].BoneMatrix2[BoneID][2][3];
		VectorCopy(vBone, Out);
	}
	else
	{
		vBone[0] = g_Player[PlayerID].BoneMatrix[BoneID][0][3];
		vBone[1] = g_Player[PlayerID].BoneMatrix[BoneID][1][3];
		vBone[2] = g_Player[PlayerID].BoneMatrix[BoneID][2][3];
		VectorCopy(vBone, Out);
	}
}
// ===================================================================================


// ===================================================================================
// Studio table hook
void HookStudioTable()
{
	DWORD dwStudioPointer = Utility->FindPattern("client.dll", "BF ? ? ? ? C7 00 ? ? ? ? F3 A5");

	Utility->DeleteLog("Studio.txt");
	Utility->Log("Studio.txt", "Studio Pointer: 0x%p (Module: 0x%p)\n", dwStudioPointer, Utility->CalcModuleOffset(dwStudioPointer));

	g_pStudio = (engine_studio_api_t*)dwStudioPointer;
	memcpy(&g_oStudio, g_pStudio, sizeof(engine_studio_api_t));
}

void UnhookStudioTable()
{
	memcpy(g_pStudio, &g_oStudio, sizeof(engine_studio_api_t));
}
// ===================================================================================