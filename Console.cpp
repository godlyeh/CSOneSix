// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Console commands
void Console::AddCommand(char* CommandName, void(__cdecl* Function)(std::string ConsoleCommand))
{
	console_cmd_t tmp;
	strcpy_s(tmp.Name, CommandName);
	tmp.Function = Function;
	ConsoleCmdStorage.push_back(tmp);
}

bool Console::HandleKeys(int keynum)
{
	// Toggle console active
	if (keynum == K_DEL)
	{
		Console::ConsoleActive = !Console::ConsoleActive;
		return true;
	}

	// Get key input
	if (Console::ConsoleActive)
	{
		if (keynum >= 97 && keynum <= 122) // a-z
		{
			EditLine += (char)keynum;
			return true;
		}

		if (keynum == K_BACKSPACE && EditLine.size() > 0)
		{
			EditLine.erase(EditLine.size() - 1);
			return true;
		}

		if (keynum >= 44 && keynum <= 57) // 0-9 ,+.-
		{
			EditLine += g_pszConsoleKeys[keynum];
			return true;
		}
	}

	return false;
}
// ===================================================================================


// ===================================================================================
// Console handler
void Console::DrawConsole(color_t color)
{
	if (ConsoleActive == false)
		return;

	// Position
	int StrH = Draw::GetStringHeight() + 5;
	int x = 380;
	int y = 200;
	int w = 640;
	int h = 480;

	// Draw window
	Draw::DrawWindow("Console", x, y, w, h, color);
	Draw::FillRGBA(x, y + h - StrH, w - 1, 1, rgb(0, 0, 0, 255));

	// Text
	Draw::DrawString(false, false, x + 2, y + h - StrH + 2, rgb(255, 255, 255), "> %s", EditLine.c_str());
	
	// Blinker
	static Timer BlinkTimer = Timer(1);
	static bool FlipFlopBlink = true;
	if (BlinkTimer.Running())
	{
		if (FlipFlopBlink)
			Draw::FillRGBA(x + 4 + Draw::GetStringWidth("> %s", EditLine.c_str()), y + h - StrH + 3, 1, StrH - 6, rgb(255, 255, 255));
	}
	else
	{
		FlipFlopBlink = !FlipFlopBlink;
		BlinkTimer.Reset();
	}
}

void Console::Add(const char* Text, ...)
{
	char Buffer[512];
	GET_VA_ARGS(Text, Buffer);

	console_entry_t tmp;
	tmp.Line = Text;
	ConsoleStorage.push_back(tmp);
}

void Console::Parse(const std::string& Text)
{
	if (Text.size() <= 0)
		return;

	std::vector<std::string> ArgumentList = Utility->SplitString(Text, ' ');
	std::string Command = ArgumentList[0];

	// hl console command
	if (Command.substr(0, 1) == "#")
	{
		
		//Line = Line.substr(1);
		return;
	}

	// console commands
	for (int i = 0; i < (int)ConsoleCmdStorage.size(); ++i)
	{
		if (Command == ConsoleCmdStorage[i].Name)
			ConsoleCmdStorage[i].Function(Text);
	}

	//Error();
}

void Console::Error(const char* Usage)
{
	Add("'%s' unknown command.", EditLine.c_str());
	if (Usage) Add("Usage: %s", Usage);
}
// ===================================================================================