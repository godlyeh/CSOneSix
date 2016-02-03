// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Hooked GL funcs
VOID APIENTRY Hooked_glBegin(GLenum mode)
{
	cl_entity_t* pEntity = g_oStudio.GetCurrentEntity();

	if (pEntity)
	{
		// Get bone matrix
		if (!g_Player[pEntity->index].GotFirstBoneMatrix)
		{
			for (int i = 0; i < MAXSTUDIOBONES; ++i)
			{
				TransformMatrix* pBoneMatrix = (TransformMatrix*)g_oStudio.StudioGetBoneTransform();
				g_Player[pEntity->index].BoneMatrix[i][0][3] = (*pBoneMatrix)[i][0][3];
				g_Player[pEntity->index].BoneMatrix[i][1][3] = (*pBoneMatrix)[i][1][3];
				g_Player[pEntity->index].BoneMatrix[i][2][3] = (*pBoneMatrix)[i][2][3];
			}

			g_Player[pEntity->index].GotFirstBoneMatrix = true;
		}
		else
		{
			for (int i = 0; i < MAXSTUDIOBONES; ++i)
			{
				TransformMatrix* pBoneMatrix = (TransformMatrix*)g_oStudio.StudioGetBoneTransform();
				g_Player[pEntity->index].BoneMatrix2[i][0][3] = (*pBoneMatrix)[i][0][3];
				g_Player[pEntity->index].BoneMatrix2[i][1][3] = (*pBoneMatrix)[i][1][3];
				g_Player[pEntity->index].BoneMatrix2[i][2][3] = (*pBoneMatrix)[i][2][3];
			}
		}

		// Wallhack
		if (Variable::Wallhack == 1)
		{
			if (EngineHelper::ValidEntity(pEntity->index))
				glDepthRange(0, 0.5);
			else
				glDepthRange(0, 1);
		}
	}

	glBegin(mode);
}
// ===================================================================================


// ===================================================================================
// OpenGL table hook
DWORD g_dwOpenGLPointer = 0;

void HookOpenGLTable()
{
	g_dwOpenGLPointer = Utility->FindPattern("hw.dll", "8B 15 ? ? ? ? D9 5D 10");
	g_dwOpenGLPointer += 0x34;
	
	Utility->DeleteLog("OpenGL.txt");
	Utility->Log("OpenGL.txt", "OpenGL Pointer: 0x%p (Module: 0x%p)\n", g_dwOpenGLPointer, Utility->CalcModuleOffset(g_dwOpenGLPointer));

	DWORD Base = Utility->GetModule("OPENGL32.dll")->BaseAddress;
	DWORD Size = Base + Utility->GetModule("OPENGL32.dll")->Size;

	for (DWORD dwPtr = g_dwOpenGLPointer; dwPtr <= g_dwOpenGLPointer + 0xB44; ++dwPtr)
	{
		DWORD dwFunction = *(PDWORD)(dwPtr);

		if (dwFunction < Base || dwFunction > Size)
			continue;

#define GL_HOOK_FUNC(name) { if (dwFunction == (DWORD)GetProcAddress(GetModuleHandle("OPENGL32.dll"), #name)) HOOK(dwPtr, Hooked_##name);/**(PDWORD)dwPtr = (DWORD)Hooked_##name;*/ }
							

		GL_HOOK_FUNC(glBegin);
	}
}

/*void UnhookOpenGLTable()
{
	for (DWORD dwPtr = g_dwOpenGLPointer; dwPtr <= g_dwOpenGLPointer + 0xB44; ++dwPtr)
	{
		DWORD dwFunction = *(PDWORD)(dwPtr);

#define GL_UNHOOK_FUNC(name) { if (dwFunction == (DWORD)Hooked_##name) *(PDWORD)dwPtr = (DWORD)##name; }


		GL_UNHOOK_FUNC(glBegin);
	}
}*/
// ===================================================================================