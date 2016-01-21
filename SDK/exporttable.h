typedef struct export_table_s
{
	int(*Initialize)(cl_enginefunc_t *pEnginefuncs,int iVersion); //0
	int(*HUD_Init)(void ); //1
	int(*HUD_VidInit)(void ); //2
	void(*HUD_Redraw)(float time,int intermission); //3
	int(*HUD_UpdateClientData)(client_data_t *pcldata,float flTime); //4
	int(*HUD_Reset)(void); //5
	void(*HUD_PlayerMove)(struct playermove_s *ppmove,int server); //6
	void(*HUD_PlayerMoveInit)(struct playermove_s *ppmove); //7
	char(*HUD_PlayerMoveTexture)(char *name); //8
	void(*IN_ActivateMouse)(void); //9
	void(*IN_DeactivateMouse)(void); //10
	void(*IN_MouseEvent)(int mstate); //11
	void(*IN_ClearStates)(void); //12
	void(*IN_Accumulate)(void); //13
	void(*CL_CreateMove)(float frametime,struct usercmd_s *cmd,int active); //14
	int(*CL_IsThirdPerson)(void); //15
	void(*CL_CameraOffset)(float *ofs); //16
	struct kbutton_s *(*KB_Find)(const char *name); //17
	void(*CAM_Think)(void); //18
	void(*V_CalcRefdef)(struct ref_params_s *pparams); //19
	int(*HUD_AddEntity)(int type,struct cl_entity_s *ent,const char *modelname); //20
	void(*HUD_CreateEntities)(void); //21
	void(*HUD_DrawNormalTriangles)(void); //22
	void(*HUD_DrawTransparentTriangles)(void); //23
	void(*HUD_StudioEvent)(const struct mstudioevent_s *event,const struct cl_entity_s *entity); //24
	void(*HUD_PostRunCmd)(struct local_state_s *from,struct local_state_s *to,struct usercmd_s *cmd,int runfuncs,double time,unsigned int random_seed); //25
	void(*HUD_Shutdown)(void); //26
	void(*HUD_TxferLocalOverrides)(struct entity_state_s *state,const struct clientdata_s *client); //27
	void(*HUD_ProcessPlayerState)(struct entity_state_s *dst,const struct entity_state_s *src); //28
	void(*HUD_TxferPredictionData)(struct entity_state_s *ps,const struct entity_state_s *pps,struct clientdata_s *pcd,const struct clientdata_s *ppcd,struct weapon_data_s *wd,const struct weapon_data_s *pwd); //29
	void(*Demo_ReadBuffer)(int size,unsigned char *buffer); //30
	int(*HUD_ConnectionlessPacket)(struct netadr_s *net_from,const char *args,char *response_buffer,int *response_buffer_size); //31
	int(*HUD_GetHullBounds)(int hullnumber,float *mins,float *maxs); //32
	void(*HUD_Frame)(double time); //33
	int(*HUD_Key_Event)(int down,int keynum,const char *pszCurrentBinding); //34
	void(*HUD_TempEntUpdate)(double frametime,double client_time,double cl_gravity,struct tempent_s **ppTempEntFree,struct tempent_s **ppTempEntActive,int (*Callback_AddVisibleEntity)(struct cl_entity_s *pEntity),void(*Callback_TempEntPlaySound)(struct tempent_s *pTemp,float damp)); //35
	struct cl_entity_s *(*HUD_GetUserEntity)(int index); //36
	int(*HUD_VoiceStatus)(int entindex,qboolean bTalking); //37
	int(*HUD_DirectorMessage)(unsigned char command,unsigned int firstObject,unsigned int secondObject,unsigned int flags); //38
	int(*HUD_GetStudioModelInterface)(int version,struct r_studio_interface_s **ppinterface,struct engine_studio_api_s *pstudio); //39
	void(*HUD_CHATINPUTPOSITION_FUNCTION)(int *x,int *y); //40
	int(*HUD_GetPlayerTeam)(int iplayer); //41
	void(*CLIENTFACTORY)(void); //42
}export_t,export_s;