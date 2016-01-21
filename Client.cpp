// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
export_t* g_pExport = NULL;
export_t g_oExport;
// ===================================================================================


// ===================================================================================
// Export functions
void HUD_Redraw(float time, int intermission)
{
	g_oExport.HUD_Redraw(time, intermission);

	if (EngineHelper::IsConnected())
	{
		
	}
}
// ===================================================================================


// ===================================================================================
// Export table hook
void HookExportTable()
{
	DWORD dwExportPointer = Utility->FindPattern("hw.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 0C E8 ? ? ? ? E8 ? ? ? ?");

	Utility->DeleteLog("Exports.txt");
	Utility->Log("Exports.txt", "Export Pointer: 0x%p (Module: 0x%p)\n", dwExportPointer, Utility->CalcModuleOffset(dwExportPointer));

	g_pExport = (export_t*)dwExportPointer;
	memcpy(&g_oExport, g_pExport, sizeof(export_t));

	g_pExport->HUD_Redraw = HUD_Redraw;
}

void UnhookExportTable()
{
	memcpy(g_pExport, &g_oExport, sizeof(export_t));
}
// ===================================================================================