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
		if (Variable::Wallhack == 1)
		{
			if (EngineHelper::ValidEntity(pEntity->index))
				glDepthRange(0, 0.5);
			else
				glDepthRange(0, 1);
		}

		if (Variable::Wallhack == 2)
		{
			float CurrentColor[4];
			GLboolean CurrentBlend = GL_FALSE;
			glGetFloatv(GL_CURRENT_COLOR, CurrentColor);
			glGetBooleanv(GL_BLEND, &CurrentBlend);

			if (!EngineHelper::ValidEntity(pEntity->index))
			{
				glDisable(GL_DEPTH_TEST);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glColor4f(CurrentColor[0], CurrentColor[1], CurrentColor[2], Variable::Wallhack_Transparency / 100.0f);
			}

			if (mode == GL_QUADS && CurrentColor[0] == 1 && CurrentColor[1] == 1 && CurrentColor[2] == 1)
			{
				float texCoords[10];
				glGetFloatv(GL_CURRENT_TEXTURE_COORDS, texCoords);
				if (texCoords[6] > 512 || texCoords[7] > 512)
					mode = GL_NONE;
			}
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