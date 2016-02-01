// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variables, etc...
event_t* g_pEventList;
// ===================================================================================


// ===================================================================================
// Events
pfnEventHook oCreateExplosive = NULL;
pfnEventHook oCreateSmoke = NULL;
pfnEventHook oDecalReset = NULL;
pfnEventHook oFamas = NULL;
pfnEventHook oGalil = NULL;
pfnEventHook oKnife = NULL;
pfnEventHook oEliteRight = NULL;
pfnEventHook oEliteLeft = NULL;
pfnEventHook oXM1014 = NULL;
pfnEventHook oUmp45 = NULL;
pfnEventHook oFiveSeven = NULL;
pfnEventHook oTmp = NULL;
pfnEventHook oSg552 = NULL;
pfnEventHook oScout = NULL;
pfnEventHook oAwp = NULL;
pfnEventHook oP228 = NULL;
pfnEventHook oP90 = NULL;
pfnEventHook oMac10 = NULL;
pfnEventHook oM4a1 = NULL;
pfnEventHook oM3 = NULL;
pfnEventHook oM249 = NULL;
pfnEventHook oGlock18 = NULL;
pfnEventHook oSg550 = NULL;
pfnEventHook oG3sg1 = NULL;
pfnEventHook oDeagle = NULL;
pfnEventHook oAug = NULL;
pfnEventHook oAk47 = NULL;
pfnEventHook oMp5n = NULL;
pfnEventHook oUsp = NULL;
pfnEventHook oVehicle = NULL;
pfnEventHook oTrain = NULL;
pfnEventHook oGaussSpin = NULL;
pfnEventHook oGauss = NULL;
pfnEventHook oPython = NULL;
pfnEventHook oMp5 = NULL;
pfnEventHook oShotgun2 = NULL;
pfnEventHook oShotgun1 = NULL;
pfnEventHook oGlock2 = NULL;
pfnEventHook oGlock1 = NULL;

int Hooked_CreateExplosive(event_args_t* args)
{
	return oCreateExplosive(args);
}

int Hooked_CreateSmoke(event_args_t* args)
{
	return oCreateSmoke(args);
}

int Hooked_DecalReset(event_args_t* args)
{
	return oDecalReset(args);
}

int Hooked_Famas(event_args_t* args)
{
	return oFamas(args);
}

int Hooked_Galil(event_args_t* args)
{
	return oGalil(args);
}

int Hooked_Knife(event_args_t* args)
{
	return oKnife(args);
}

int Hooked_EliteRight(event_args_t* args)
{
	return oEliteRight(args);
}

int Hooked_EliteLeft(event_args_t* args)
{
	return oEliteLeft(args);
}

int Hooked_XM1014(event_args_t* args)
{
	return oXM1014(args);
}

int Hooked_Ump45(event_args_t* args)
{
	return oUmp45(args);
}

int Hooked_FiveSeven(event_args_t* args)
{
	return oFiveSeven(args);
}

int Hooked_Tmp(event_args_t* args)
{
	return oTmp(args);
}

int Hooked_Sg552(event_args_t* args)
{
	return oSg552(args);
}

int Hooked_Scout(event_args_t* args)
{
	return oScout(args);
}

int Hooked_Awp(event_args_t* args)
{
	return oAwp(args);
}

int Hooked_P228(event_args_t* args)
{
	return oP228(args);
}

int Hooked_P90(event_args_t* args)
{
	return oP90(args);
}

int Hooked_Mac10(event_args_t* args)
{
	return oMac10(args);
}

int Hooked_M4a1(event_args_t* args)
{
	return oM4a1(args);
}

int Hooked_M3(event_args_t* args)
{
	return oM3(args);
}

int Hooked_M249(event_args_t* args)
{
	return oM249(args);
}

int Hooked_Glock18(event_args_t* args)
{
	return oGlock18(args);
}

int Hooked_Sg550(event_args_t* args)
{
	return oSg550(args);
}

int Hooked_G3sg1(event_args_t* args)
{
	return oG3sg1(args);
}

int Hooked_Deagle(event_args_t* args)
{
	return oDeagle(args);
}

int Hooked_Aug(event_args_t* args)
{
	return oAug(args);
}

int Hooked_Ak47(event_args_t* args)
{
	return oAk47(args);
}

int Hooked_Mp5n(event_args_t* args)
{
	return oMp5n(args);
}

int Hooked_Usp(event_args_t* args)
{
	return oUsp(args);
}

int Hooked_Vehicle(event_args_t* args)
{
	return oVehicle(args);
}

int Hooked_Train(event_args_t* args)
{
	return oTrain(args);
}

int Hooked_GaussSpin(event_args_t* args)
{
	return oGaussSpin(args);
}

int Hooked_Gauss(event_args_t* args)
{
	return oGauss(args);
}

int Hooked_Python(event_args_t* args)
{
	return oPython(args);
}

int Hooked_Mp5(event_args_t* args)
{
	return oMp5(args);
}

int Hooked_Shotgun2(event_args_t* args)
{
	return oShotgun2(args);
}

int Hooked_Shotgun1(event_args_t* args)
{
	return oShotgun1(args);
}

int Hooked_Glock2(event_args_t* args)
{
	return oGlock2(args);
}

int Hooked_Glock1(event_args_t* args)
{
	return oGlock1(args);
}
// ===================================================================================


// ===================================================================================
// Event list hook
void HookEventList()
{
	DWORD dwEventListPointer = Utility->FindPattern("hw.dll", "8B 35 ? ? ? ? 57 8B 7D 08");
	dwEventListPointer = *(PDWORD)dwEventListPointer;

	Utility->DeleteLog("Events.txt");
	Utility->Log("Events.txt", "Event List Pointer: 0x%p (Module: 0x%p)\n", dwEventListPointer, Utility->CalcModuleOffset(dwEventListPointer));

	g_pEventList = (event_t*)dwEventListPointer;

	while (g_pEventList)
	{
		Utility->Log("Events.txt", " [EventList][0x%p] %s = 0x%p (Module: 0x%p)\n", g_pEventList, g_pEventList->Name, g_pEventList->Function, Utility->CalcModuleOffset((DWORD)g_pEventList));
#define HookEvent(name, func) { if (!_stricmp(g_pEventList->Name, name)) { \
										o##func = (pfnEventHook)g_pEventList->Function; \
										HOOK(&g_pEventList->Function, Hooked_##func); } }
		
		HookEvent("events/createexplo.sc", CreateExplosive);
		HookEvent("events/createsmoke.sc", CreateSmoke);
		HookEvent("events/decal_reset.sc", DecalReset);
		HookEvent("events/famas.sc", Famas);
		HookEvent("events/galil.sc", Galil);
		HookEvent("events/knife.sc", Knife);
		HookEvent("events/elite_right.sc", EliteRight);
		HookEvent("events/elite_left.sc", EliteLeft);
		HookEvent("events/xm1014.sc", XM1014);
		HookEvent("events/ump45.sc", Ump45);
		HookEvent("events/fiveseven.sc", FiveSeven);
		HookEvent("events/tmp.sc", Tmp);
		HookEvent("events/sg552.sc", Sg552);
		HookEvent("events/scout.sc", Scout);
		HookEvent("events/awp.sc", Awp);
		HookEvent("events/p228.sc", P228);
		HookEvent("events/p90.sc", P90);
		HookEvent("events/mac10.sc", Mac10);
		HookEvent("events/m4a1.sc", M4a1);
		HookEvent("events/m3.sc", M3);
		HookEvent("events/m249.sc", M249);
		HookEvent("events/glock18.sc", Glock18);
		HookEvent("events/sg550.sc", Sg550);
		HookEvent("events/g3sg1.sc", G3sg1);
		HookEvent("events/deagle.sc", Deagle);
		HookEvent("events/aug.sc", Aug);
		HookEvent("events/ak47.sc", Ak47);
		HookEvent("events/mp5n.sc", Mp5n);
		HookEvent("events/usp.sc", Usp);
		HookEvent("events/vehicle.sc", Vehicle);
		HookEvent("events/train.sc", Train);
		HookEvent("events/gaussspin.sc", GaussSpin);
		HookEvent("events/gauss.sc", Gauss);
		HookEvent("events/python.sc", Python);
		HookEvent("events/mp5.sc", Mp5);
		HookEvent("events/shotgun2.sc", Shotgun2);
		HookEvent("events/shotgun1.sc", Shotgun1);
		HookEvent("events/glock2.sc", Glock2);
		HookEvent("events/glock1.sc", Glock1);

		g_pEventList = g_pEventList->Next;
	}

	g_pEventList = (event_t*)dwEventListPointer;
}

void UnhookEventList()
{

}
// ===================================================================================