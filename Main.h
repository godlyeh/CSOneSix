// ===================================================================================
// Includes
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Opengl32.lib")

#include <Windows.h>
#include <IOStream>
#include <FStream>
#include <String>
#include <SStream>
#include <Vector>
#include <Psapi.h>
#include <TlHelp32.h>
#include <GL\GL.h>
#include <gl\GLU.h>

#include "SDK/wrect.h"
#include "SDK/cl_dll.h"
#include "SDK/cvardef.h"
#include "SDK/pmtrace.h" 
#include "SDK/r_studioint.h"
#include "SDK/triangleapi.h"
#include "SDK/r_efx.h"
#include "SDK/studio.h"
#include "SDK/event_api.h"
#include "SDK/parsemsg.h"
#include "SDK/ref_params.h"
#include "SDK/com_model.h"
#include "SDK/screenfade.h"
#include "SDK/usercmd.h"
#include "SDK/pm_defs.h"
#include "SDK/exporttable.h"
#include "SDK/util.h"
#include "SDK/net_api.h"
#include "SDK/keydefs.h"
#include "SDK/mathlib.h"

#include "ADE32.h"
#include "Drawing.h"
#include "Console.h"
#include "Hooking.h"
#include "Variables.h"
#include "Menu.h"
#include "EntityInfo.h"
#include "Timer.h"
#include "Utility.h"

#include "Client.h"
#include "Command.h"
#include "CVar.h"
#include "Engine.h"
#include "ESP.h"
#include "Event.h"
#include "HudMessage.h"
#include "KButton.h"
#include "OpenGL32.h"
#include "Sound.h"
#include "Studio.h"
#include "UserMessage.h"
// ===================================================================================


// ===================================================================================
// Externals
extern char g_szHackDir[MAX_PATH];
// ===================================================================================