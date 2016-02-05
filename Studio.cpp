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

void StudioHelper::GetPlayerBone(int PlayerID, int BoneID, float* Out)
{
	Vector vBone;

	vBone[0] = g_Player[PlayerID].BoneMatrix[BoneID][0][3];
	vBone[1] = g_Player[PlayerID].BoneMatrix[BoneID][1][3];
	vBone[2] = g_Player[PlayerID].BoneMatrix[BoneID][2][3];
	VectorCopy(vBone, Out);
}

bool StudioHelper::IsVisible(int PlayerID)
{
	// Do main trace first
	Vector vMainPos;
	Aimbot::GetAimVector(PlayerID, vMainPos);
	if (EngineHelper::IsPointVisible(vMainPos))
		return true;

	// Loop bones
	for (int i = 0; i < 33; ++i)
		if (g_Player[PlayerID].BoneVisible[i] == true)
			return true;

	return false;
}
// ===================================================================================


// ===================================================================================
// Studio hooks
int StudioCheckBBox() // Force studio to check bounding boxes (for hitbox on players behind)
{
	cl_entity_t* pEntity = g_oStudio.GetCurrentEntity();
	if (EngineHelper::ValidPlayer(pEntity->index))
		return 1;

	return g_oStudio.StudioCheckBBox();
}

void RestoreRenderer()
{
	cl_entity_t* pEntity = g_oStudio.GetCurrentEntity();

	if (EngineHelper::ValidPlayer(pEntity->index))
	{
		if (!g_Player[pEntity->index].bGotBoneMatrix)
		{
			for (int i = 0; i < 33; ++i)
			{
				TransformMatrix* pBoneMatrix = (TransformMatrix*)g_oStudio.StudioGetBoneTransform();
				Vector vPoint = Vector((*pBoneMatrix)[i][0][3], (*pBoneMatrix)[i][1][3], (*pBoneMatrix)[i][2][3]);

				g_Player[pEntity->index].BoneMatrix[i][0][3] = vPoint.x;
				g_Player[pEntity->index].BoneMatrix[i][1][3] = vPoint.y;
				g_Player[pEntity->index].BoneMatrix[i][2][3] = vPoint.z;
				g_Player[pEntity->index].BoneVisible[i] = EngineHelper::IsPointVisible(vPoint);
			}

			g_Player[pEntity->index].Visible = StudioHelper::IsVisible(pEntity->index);
			g_Player[pEntity->index].bGotBoneMatrix = true;
		}
	}

	g_oStudio.RestoreRenderer();
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

	g_pStudio->RestoreRenderer = RestoreRenderer;
	g_pStudio->StudioCheckBBox = StudioCheckBBox;
}

void UnhookStudioTable()
{
	memcpy(g_pStudio, &g_oStudio, sizeof(engine_studio_api_t));
}
// ===================================================================================