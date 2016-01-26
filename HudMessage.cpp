// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Hud messages
void HudMessage::Add(char* Message, ...)
{
	char Buffer[512];
	GET_VA_ARGS(Message, Buffer);

	HudMessageInfo tmp = HudMessageInfo(Buffer);
	HudMessageStorage.insert(HudMessageStorage.begin(), tmp);
}

void HudMessage::Clear()
{
	HudMessageStorage.clear();
}

void HudMessage::Draw()
{
	for (int i = 0; i < ((HudMessageStorage.size() < MAX_HUD_MESSAGE) ? (int)HudMessageStorage.size() : MAX_HUD_MESSAGE); ++i)
	{
		if (HudMessageStorage[i].Timeout.Running())
		{
			int x = g_ScreenInfo.iWidth / 2;
			int y = (g_ScreenInfo.iHeight - Draw::GetStringHeight() - 55) - i * (Draw::GetStringHeight() + 2);

			Draw::DrawString(true, true, x, y, rgb(255, 0, 0), HudMessageStorage[i].Message);
		}
	}
}
// ===================================================================================