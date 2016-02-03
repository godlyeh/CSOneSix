// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Console commands
void Console::AddCommand(char* CommandName, void(__cdecl* Function)(std::string ConsoleCommand))
{
	console_cmd_t tmp; ZeroMemory(&tmp, sizeof(console_cmd_t));
	strcpy_s(tmp.Name, CommandName);
	tmp.Function = Function;
	ConsoleCmdStorage.push_back(tmp);
}

bool Console::ShiftKeyHeld()
{
	return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}

bool Console::CapslockActive()
{
	return (GetKeyState(VK_CAPITAL) & 1) != 0;
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
#define HandleKey(a) { EditLine.insert(EditPos, a); EditPos += strlen(a); return true; }
#define ShiftHeld ShiftKeyHeld()
#define CapsLock CapslockActive()

		if (keynum == K_ENTER) // Execute command
		{
			Parse(EditLine);
			EditLine.clear();
			EditPos = 0;
			return true;
		}

		if (keynum == K_BACKSPACE) // Erase line
		{
			if (EditLine.size() > 0 && EditPos > 0)
			{
				--EditPos;
				EditLine.erase(EditPos, 1);
			}
			
			return true;
		}

		if (keynum == K_LEFTARROW)
		{
			if (EditPos > 0) --EditPos;
			return true;
		}

		if (keynum == K_RIGHTARROW && EditPos < (int)EditLine.size())
		{
			if (EditPos < (int)EditLine.size()) ++EditPos;
			return true;
		}

		if (keynum == K_SPACE)
			HandleKey(" ");

		if (keynum == K_TAB)
		{
			HandleKey("    ");
		}

		if (keynum >= 97 && keynum <= 122) // a-z
		{
			if (CapsLock && ShiftHeld == false ||
				CapsLock == false && ShiftHeld)
			{
				HandleKey(g_pszConsoleShiftKeys[keynum]);
			}
			else
			{
				HandleKey(g_pszConsoleKeys[keynum]);
			}
		}

		if (keynum >= 44 && keynum <= 61 || keynum == 92) // 0-9 ,+.-'    and    !"#¤%&/()?=` ;:_*

		{
			if (ShiftHeld == false)
			{
				HandleKey(g_pszConsoleKeys[keynum]);
			}
			else
			{
				HandleKey(g_pszConsoleShiftKeys[keynum]);
			}
		}

		if (keynum == 93) //^^
			HandleKey(g_pszConsoleShiftKeys[keynum]);

		if (keynum == 96) // |
		{
			HandleKey(g_pszConsoleKeys[keynum]);
		}

		if (keynum == 170) //numpad 0 and Insert
			HandleKey("0");

		if (keynum == 166) //numpad 1 and End
			HandleKey("1");
		if (keynum == 167) //numpad 2 and Down arrow
			HandleKey("2");
		if (keynum == 168) //numpad 3 and Page down
			HandleKey("3");

		if (keynum == 163) //numpad 4 and Left arrow
			HandleKey("4");
		if (keynum == 164) //numpad 5
			HandleKey("5");
		if (keynum == 165) //numpad 6 and Right arrow
			HandleKey("6");

		if (keynum == 160) //numpad 7 and Home
			HandleKey("7");
		if (keynum == 161) //numpad 8 and Up arrow
			HandleKey("8");
		if (keynum == 162) //numpad 9 and Page up
			HandleKey("9");
	}

	return false;
}
// ===================================================================================


// ===================================================================================
// Console default commands
void ConFunc_conexec(std::string ConsoleCommand)
{
	if (ConsoleCommand.size() <= 8)
	{
		Console::Error("Example usage: conexec bind mouse1 +attack", NULL);
		return;
	}

	std::string ConCmd = ConsoleCommand.substr(8);
	g_oEngine.pfnClientCmd(Utility->StringA("%s", ConCmd.c_str()));
}

void ConFunc_conprint(std::string ConsoleCommand)
{
	if (ConsoleCommand.size() <= 9)
	{
		Console::Error("Example usage: conrpint Hello World", NULL);
		return;
	}

	std::string ConCmd = ConsoleCommand.substr(9);
	g_oEngine.pfnConsolePrint(Utility->StringA("%s\n", ConCmd.c_str()));
}

void Console::InitializeDefaultCommands()
{
	ADD_CON_CMD(conexec);
	ADD_CON_CMD(conprint);
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
	int MaxConsoleEntry = 25;
	int ConHeight = Draw::GetStringHeight() * MaxConsoleEntry;
	int x = 380;
	int y = 200;
	int w = 640;
	int h = ConHeight;

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
			Draw::FillRGBA(x + 1 + (EditPos > 0 ? Draw::GetStringWidth("> %s", EditLine.substr(0, EditPos).c_str()) : Draw::GetStringWidth("> ")), y + h - StrH + 3, 1, StrH - 6, rgb(255, 255, 255));
	}
	else
	{
		FlipFlopBlink = !FlipFlopBlink;
		BlinkTimer.Reset();
	}

	// Console commands
	for (int i = 0; i < ((int)ConsoleStorage.size() < MaxConsoleEntry - 1 ? (int)ConsoleStorage.size() : MaxConsoleEntry - 2); ++i)
	{
		Draw::DrawString(false, x + 5, y + 5 + i * Draw::GetStringHeight(), rgb(255, 255, 255), "%s", ConsoleStorage[i].Line.c_str());
	}
}

void Console::Add(const char* Text, ...)
{
	char Buffer[512];
	GET_VA_ARGS(Text, Buffer);

	console_entry_t tmp;
	tmp.Line = Buffer;
	ConsoleStorage.insert(ConsoleStorage.begin(), tmp);
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
		Parse(Utility->StringA("conexec %s", Text.substr(1).c_str()));
		return;
	}

	// hl console print
	if (Command.substr(0, 1) == "!")
	{
		Parse(Utility->StringA("conprint %s", Text.substr(1).c_str()));
		return;
	}

	// console commands
	for (int i = 0; i < (int)ConsoleCmdStorage.size(); ++i)
	{
		if (Command == ConsoleCmdStorage[i].Name)
		{
			if (ConsoleCmdStorage[i].Function == NULL)
			{
				Error("'%s' is missing command function!", Command.c_str());
				return;
			}
			
			Add(Text.c_str());
			ConsoleCmdStorage[i].Function(Text);
			return;
		}
	}

	Error("'%s' unknown command.", Text.c_str());
}

void Console::Error(const char* ErrorMsg, ...)
{
	char Buffer[1024];
	GET_VA_ARGS(ErrorMsg, Buffer);
	Add(Buffer);
}
// ===================================================================================