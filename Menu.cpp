// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Menu handler
char mnuToggleModifier[][32] = { "OFF", "ON" };

void Menu::FillMenuArray()
{
	MenuStorage.clear();
	static int ESP = 0;

	if (RegisterEntry("ESP", &ESP))
	{
		RegisterEntry("Name", 1, NULL, mnuToggleModifier);
		RegisterEntry("HeightCorrection", 0.5f, "Height Correction");
	}
}

void Menu::DrawMenu(color_t color, color_t selection)
{
	// Return if menu active is false
	if (MenuActive == false)
		return;

	// Fill menu entries
	FillMenuArray();

	// Position menu
	int StrH = Draw::GetStringHeight() + 2;
	int x = 25;
	int y = 200;
	int w = 280;
	int h = MenuStorage.size() * StrH;

	// Draw menu
	Draw::DrawWindow("Menu", x, y, w, h, color);

	// Loop entries and draw
	for (int i = 0; i < (int)MenuStorage.size(); ++i)
	{
		// Draw selection
		if (i == MenuIndex)
			Draw::FillRGBA(x + 1, y + StrH * i, w - 2, StrH, selection);

		// Entry to draw
		menuentry_t* Entry = &MenuStorage[i];
		static color_t clrText = rgb(255, 255, 255);
		
		// Entry position
		int X = x + 10;
		int Y = (y + 1) + StrH * i;

		// Position sub item
		if (Entry->SubItem) X += (10 * Entry->SubItem);

		// Check if its a variable or sub menu toggle
		if (Entry->IsVariable == false)
		{
			if (*(PINT)Entry->pVariable == 0)	Draw::DrawString(false, X, Y, clrText, "+ %s", Entry->Name);
			else								Draw::DrawString(false, X, Y, clrText, "- %s", Entry->Name);
		}
		else
		{
			// Draw variable entry
			Draw::DrawString(false, X, Y, clrText, Entry->Name);
			if (Entry->Value == NULL)
			{
				if (Entry->Type == eEntryType::ENTRY_INTEGER)	Draw::DrawString(false, x + w - Draw::GetStringWidth("%i", *(PINT)Entry->pVariable) - 10, Y, clrText, "%i", *(PINT)Entry->pVariable);
				if (Entry->Type == eEntryType::ENTRY_FLOAT)		Draw::DrawString(false, x + w - Draw::GetStringWidth("%.2f", *(PFLOAT)Entry->pVariable) - 10, Y, clrText, "%.2f", *(PFLOAT)Entry->pVariable);
			}
			else
				Draw::DrawString(false, x + w - Draw::GetStringWidth(Entry->Value) - 10, Y, clrText, Entry->Value);
		}
	}
}

bool Menu::HandleKeys(int keynum)
{
	// Change menu active
	if (keynum == K_INS || keynum == K_DEL)
	{
		MenuActive = !MenuActive;

		if (MenuActive == false)
			Variable::Save("Variables.cfg");

		return true;
	}

	if (MenuActive)
	{
		// Move menu index
		if (keynum == K_MWHEELUP || keynum == K_UPARROW)
		{
			--MenuIndex;
			if (MenuIndex < 0)
				MenuIndex = (int)MenuStorage.size() - 1;

			return true;
		}

		if (keynum == K_MWHEELDOWN || keynum == K_DOWNARROW)
		{
			++MenuIndex;
			if (MenuIndex >= (int)MenuStorage.size())
				MenuIndex = 0;

			return true;
		}

		// Change variable
		menuentry_t* Entry = &MenuStorage[MenuIndex];
		int iOldValue = *(PINT)Entry->pVariable;
		float flOldValue = *(PFLOAT)Entry->pVariable;

		if (keynum == K_MOUSE1 || keynum == K_RIGHTARROW)
		{
			if (Entry->Type == eEntryType::ENTRY_INTEGER)
			{
				*(PINT)Entry->pVariable += (int)Entry->Step;
				if (*(PINT)Entry->pVariable > (int)Entry->Max)		*(PINT)Entry->pVariable = (int)Entry->Min;
				if (Entry->IsVariable) HudMessage::Add("'%s' changed from '%i' to '%i'.", Entry->Name, iOldValue, *(PINT)Entry->pVariable);
			}

			if (Entry->Type == eEntryType::ENTRY_FLOAT)
			{
				*(PFLOAT)Entry->pVariable += Entry->Step;
				if (*(PFLOAT)Entry->pVariable > Entry->Max)		*(PFLOAT)Entry->pVariable = Entry->Min;
				if (Entry->IsVariable) HudMessage::Add("'%s' changed from '%.2f' to '%.2f'.", Entry->Name, flOldValue, *(PFLOAT)Entry->pVariable);
			}

			return true;
		}

		if (keynum == K_MOUSE2 || keynum == K_LEFTARROW)
		{
			if (Entry->Type == eEntryType::ENTRY_INTEGER)
			{
				*(PINT)Entry->pVariable -= (int)Entry->Step;
				if (*(PINT)Entry->pVariable < (int)Entry->Min)		*(PINT)Entry->pVariable = (int)Entry->Max;
				if (Entry->IsVariable) HudMessage::Add("'%s' changed from '%i' to '%i'.", Entry->Name, iOldValue, *(PINT)Entry->pVariable);
			}

			if (Entry->Type == eEntryType::ENTRY_FLOAT)
			{
				*(PFLOAT)Entry->pVariable -= Entry->Step;
				if (*(PFLOAT)Entry->pVariable < Entry->Min)		*(PFLOAT)Entry->pVariable = Entry->Max;
				if (Entry->IsVariable) HudMessage::Add("'%s' changed from '%.2f' to '%.2f'.", Entry->Name, flOldValue, *(PFLOAT)Entry->pVariable);
			}

			return true;
		}
	}

	return false;
}

bool Menu::RegisterEntry(char* Name, int* pVariable, int SubItem)
{
	menuentry_t tmp; ZeroMemory(&tmp, sizeof(menuentry_t));

	strcpy_s(tmp.Name, Name);
	tmp.SubItem = SubItem;
	tmp.IsVariable = false;
	tmp.Type = eEntryType::ENTRY_INTEGER;
	tmp.pVariable = pVariable;
	tmp.Step = 1;
	tmp.Min = 0;
	tmp.Max = 1;

	MenuStorage.push_back(tmp);

	return *pVariable != 0;
}

void Menu::RegisterEntry(char* Name, eEntryType Type, void* pVariable, float Step, float Min, float Max, char* CustomValue[32], int SubItem)
{
	menuentry_t tmp; ZeroMemory(&tmp, sizeof(menuentry_t));

	strcpy_s(tmp.Name, Name);
	if (CustomValue != NULL && Type == eEntryType::ENTRY_INTEGER) tmp.Value = CustomValue[*(PINT)pVariable];
	tmp.SubItem = SubItem;
	tmp.IsVariable = true;
	tmp.Type = Type;
	tmp.pVariable = pVariable;
	tmp.Step = Step;
	tmp.Min = Min;
	tmp.Max = Max;

	MenuStorage.push_back(tmp);
}

void Menu::RegisterEntry(const char* Variable, float Step, char* CustomName, char CustomValue[][32], int SubItem)
{
	variable_t* pVar = Variable::GetVariable(Variable);
	if (!pVar) return;

	menuentry_t tmp; ZeroMemory(&tmp, sizeof(menuentry_t));

	if (CustomName != NULL)	strcpy_s(tmp.Name, CustomName);
	else					strcpy_s(tmp.Name, pVar->Name);
	if (CustomValue != NULL && pVar->Type == eEntryType::ENTRY_INTEGER) tmp.Value = CustomValue[*(PINT)pVar->pVariable];
	tmp.SubItem = SubItem;
	tmp.IsVariable = true;
	tmp.Type = (eEntryType)pVar->Type;
	tmp.pVariable = pVar->pVariable;
	tmp.Step = Step;
	tmp.Min = pVar->Min;
	tmp.Max = pVar->Max;

	MenuStorage.push_back(tmp);
}
// ===================================================================================