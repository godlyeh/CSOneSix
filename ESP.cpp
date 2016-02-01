// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// ESP handler
void ESP::DrawPlayer(int PlayerID)
{
	if (EngineHelper::ValidPlayer(PlayerID) == false)
		return;
}

void ESP::DrawWeapon(int EntityID)
{
	if (EngineHelper::ValidEntity(EntityID) == false)
		return;

	Vector vScreen;
	cl_entity_t* pEntity = g_oEngine.GetEntityByIndex(EntityID);

	if (EngineHelper::WorldToScreen(pEntity->origin, vScreen) == false)
		return;

	Draw::DrawString(true, true, vScreen, rgb(255, 255, 0), pEntity->model->name);
}

void ESP::DrawEntity(int EntityID)
{

}

void ESP::DrawESP()
{
	// Loop through players and draw
	for (int i = 0; i <= MAX_CLIENTS; ++i)
		DrawPlayer(i);

	// Loop through entities and draw
	for (int i = MAX_CLIENTS; i <= 1024; ++i)
	{
		DrawWeapon(i);
		DrawEntity(i);
	}
}
// ===================================================================================