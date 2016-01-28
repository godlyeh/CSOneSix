// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================


// ===================================================================================
// Variable handlers
void Variable::Initialize()
{
	VariableStorage.clear();

#define REGISTER_INT(var, min, max) Register(#var, eVariableType::VAR_INTEGER, &var, min, max);
#define REGISTER_FLOAT(var, min, max) Register(#var, eVariableType::VAR_FLOAT, &var, min, max);

	REGISTER_INT(Name, 0, 1);
	//REGISTER_INT(MaxHudMessages, 1, 10);
	REGISTER_FLOAT(HeightCorrection, -25, 25);

	Load("Variables.cfg");
	Save("Variables.cfg");
}

void Variable::Register(char* Name, eVariableType Type, void* pVariable, float Min, float Max)
{
	variable_t tmp;

	strcpy_s(tmp.Name, Name);
	tmp.Type = Type;
	tmp.pVariable = pVariable;
	tmp.Min = Min;
	tmp.Max = Max;

	if (tmp.Type == eVariableType::VAR_INTEGER) tmp.Default = (float)(*(PINT)pVariable);
	if (tmp.Type == eVariableType::VAR_FLOAT) tmp.Default = *(PFLOAT)pVariable;

	VariableStorage.push_back(tmp);
}

variable_t* Variable::GetVariable(const char* Name)
{
	for (int i = 0; i < (int)VariableStorage.size(); ++i)
		if (!_stricmp(Name, VariableStorage[i].Name))
			return &VariableStorage[i];

	return NULL;
}

void Variable::Save(char* FileName)
{
	char FilePath[MAX_PATH];
	strcpy_s(FilePath, HACKDIR(FileName));
	std::fstream File;
	File.open(FilePath, std::fstream::out);
	if (!File.is_open())
		return;

	for (int i = 0; i < (int)VariableStorage.size(); ++i)
	{
		File << VariableStorage[i].Name << " = ";
		if (VariableStorage[i].Type == eVariableType::VAR_INTEGER) File << *(PINT)VariableStorage[i].pVariable;
		if (VariableStorage[i].Type == eVariableType::VAR_FLOAT) File << *(PFLOAT)VariableStorage[i].pVariable;
		if (i < (int)VariableStorage.size() - 1) File << std::endl;
	}

	HudMessage::Add("Saved variables to '%s'.", FileName);
	File.close();
}

void Variable::Load(char* FileName)
{
	char FilePath[MAX_PATH];
	strcpy_s(FilePath, HACKDIR(FileName));
	std::fstream File;
	File.open(FilePath, std::fstream::in);
	if (!File.is_open())
		return;

	std::string Line;
	while (!File.eof())
	{
		Line.clear();
		std::getline(File, Line);
		if (Line.find('=') == EOF)
			continue;

		std::string strVariable = Line.substr(0, Line.find('='));
		std::string strValue = Line.substr(Line.find('=') + 1);
		Utility->ReplaceString((char*)strVariable.c_str(), " ", "");
		Utility->ReplaceString((char*)strValue.c_str(), " ", "");
		
		variable_t* pVar = GetVariable(strVariable.c_str());
		if (pVar == NULL)
			continue;

		if (pVar->Type == eVariableType::VAR_INTEGER)
		{
			if (strValue.find_first_not_of("1234567890.") == EOF || strValue.size() <= 0) *(PINT)pVar->pVariable = (int)pVar->Default;
			else *(PINT)pVar->pVariable = (int)atof(strValue.c_str());

			if (*(PINT)pVar->pVariable < (int)pVar->Min) *(PINT)pVar->pVariable = (int)pVar->Min;
			if (*(PINT)pVar->pVariable > (int)pVar->Max) *(PINT)pVar->pVariable = (int)pVar->Max;
		}

		if (pVar->Type == eVariableType::VAR_FLOAT)
		{
			if (strValue.find_first_not_of("1234567890.") == EOF || strValue.size() <= 0) *(PFLOAT)pVar->pVariable = pVar->Default;
			else *(PFLOAT)pVar->pVariable = (float)atof(strValue.c_str());

			if (*(PFLOAT)pVar->pVariable < pVar->Min) *(PFLOAT)pVar->pVariable = pVar->Min;
			if (*(PFLOAT)pVar->pVariable > pVar->Max) *(PFLOAT)pVar->pVariable = pVar->Max;
		}

		Utility->Log("Log.txt", "%s = %.2f %i\n", strVariable.c_str(), *(PFLOAT)pVar->pVariable, *(PINT)pVar->pVariable);
	}

	HudMessage::Add("Loaded variables from '%s'.", FileName);
	File.close();
}
// ===================================================================================