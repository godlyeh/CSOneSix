// ===================================================================================
// External variables
extern globalvars_t* g_pGlobals;
extern export_t* g_pExport;
extern export_t g_oExport;
// ===================================================================================


// ===================================================================================
// External funcs
void AtMapChange();
void AtRoundStart();
// ===================================================================================


// ===================================================================================
// Export table hook
void HookExportTable();
void UnhookExportTable();
// ===================================================================================