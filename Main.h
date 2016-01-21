// ===================================================================================
// Includes
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Opengl32.lib")

#include <Windows.h>
#include <IOStream>
#include <FStream>
#include <Vector>
#include <Psapi.h>
#include <GL\GL.h>

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

#include "ADE32.h"
#include "Utility.h"

#include "Client.h"
#include "Command.h"
#include "CVar.h"
#include "Drawing.h"
#include "Engine.h"
#include "Event.h"
#include "KButton.h"
#include "Studio.h"
#include "UserMessage.h"
// ===================================================================================


// ===================================================================================
// Externals
extern char g_szHackDir[MAX_PATH];
// ===================================================================================