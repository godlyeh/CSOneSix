// ===================================================================================
// Includes
#include "Main.h"
// ===================================================================================
UtilityHandler* Utility = new UtilityHandler;


// ===================================================================================
// String handlers
char *UtilityHandler::StringA(const char* Text, ...)
{
	static char Buffer[1024]; ZeroMemory(&Buffer, sizeof(Buffer));
	GET_VA_ARGS(Text, Buffer);
	return Buffer;
}

void UtilityHandler::ReplaceString(char* Text, char* SearchText, char* TextToReplace)
{
	std::string strRet = std::string(Text);
	while (strRet.find(SearchText) != -1) strRet.replace(strRet.find(SearchText), strlen(SearchText), TextToReplace);
	strcpy_s(Text, strRet.size() + 1, strRet.c_str());
}

std::vector<std::string> &UtilityHandler::SplitString(const std::string &String, char c, std::vector<std::string> &Elements)
{
	std::stringstream StringStream(String);
	std::string Element;
	while (std::getline(StringStream, Element, c))
		Elements.push_back(Element);
	return Elements;
}

std::vector<std::string> UtilityHandler::SplitString(const std::string &String, char c)
{
	std::vector<std::string> Elements;
	SplitString(String, c, Elements);
	return Elements;
}

std::string UtilityHandler::GetStringArg(const std::string &String, int Arg)
{
	std::vector<std::string> ArgumentList = SplitString(String, ' ');
	if (Arg >= (int)ArgumentList.size())
		return NULL;

	return ArgumentList[Arg];
}
// ===================================================================================


// ===================================================================================
// File handling
bool UtilityHandler::FileExist(char* FileName)
{
	FILE* pFile = NULL;
	if (!fopen_s(&pFile, HACKDIR(FileName), "r"))
	{
		fclose(pFile);
		return true;
	}

	return false;
}

void UtilityHandler::Log(char* FileName, const char* Text, ...)
{
	char Buffer[10240];
	GET_VA_ARGS(Text, Buffer);

	std::fstream File;
	File.open(HACKDIR(FileName), std::fstream::out | std::fstream::app);
	if (!File.is_open())
		return;

	File << Buffer;
	File.close();
}

void UtilityHandler::DeleteLog(char* FileName)
{
	if (FileExist(FileName))
		DeleteFile(HACKDIR(FileName));
}
// ===================================================================================


// ===================================================================================
// Module list
ModuleInfo* UtilityHandler::GetModule(char *Module, DWORD BaseAddress)
{
	for (int i = 0; i < (int)Modules.size(); ++i)
	{
		if (_stricmp(Module, Modules[i].Name))
			continue;

		if (BaseAddress == 0)
			return &Modules[i];

		if (BaseAddress == Modules[i].BaseAddress)
			return &Modules[i];
	}

	return NULL;
}

void UtilityHandler::GenerateModuleList()
{
	DWORD dwAddress = 0x0;
	DWORD dwEnd = 0x7FFFFFFF;

	HANDLE hProcess = GetCurrentProcess();
	Modules.clear();

	_MEMORY_BASIC_INFORMATION mbi;
	while (VirtualQuery((LPVOID)dwAddress, &mbi, sizeof(_MEMORY_BASIC_INFORMATION)))
	{
		if (mbi.Type == MEM_IMAGE && mbi.State == MEM_COMMIT)
		{
			char FileName[MAX_PATH];
			GetMappedFileName(hProcess, (void*)dwAddress, FileName, MAX_PATH);
			strcpy_s(FileName, strrchr(FileName, '\\') + 1);

			if (GetModule(FileName, (DWORD)mbi.AllocationBase) == NULL)
			{
				ModuleInfo Tmp; ZeroMemory(&Tmp, sizeof(ModuleInfo));
				strcpy_s(Tmp.Name, FileName);
				Tmp.BaseAddress = (DWORD)mbi.AllocationBase;
				Tmp.Size = mbi.RegionSize;
				Modules.push_back(Tmp);
			}
			else GetModule(FileName, (DWORD)mbi.AllocationBase)->Size += mbi.RegionSize;
		}

		dwAddress += mbi.RegionSize;
	}

	CloseHandle(hProcess);
}
// ===================================================================================


// ===================================================================================
// Memory handling
THREADENTRY32* UtilityHandler::GetProcessThread()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	static THREADENTRY32 te32; ZeroMemory(&te32, sizeof(te32));
	te32.dwSize = sizeof(THREADENTRY32);

	Thread32First(hSnapshot, &te32);
	while (Thread32Next(hSnapshot, &te32))
	{
		if (te32.th32OwnerProcessID == GetCurrentProcessId() && te32.th32ThreadID != GetCurrentThreadId())
		{
			CloseHandle(hSnapshot);
			return &te32;
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

DWORD UtilityHandler::CalcModuleOffset(DWORD Address)
{
	DWORD Base = 0;

	for (int i = 0; i < (int)Modules.size(); ++i)
	{
		if (Address < Modules[i].BaseAddress || Address > Modules[i].BaseAddress + Modules[i].Size)
			continue;

		if (!_stricmp(Modules[i].Name, "hw.dll")) Base = 0x1D00000;
		if (!_stricmp(Modules[i].Name, "client.dll")) Base = 0x1900000;

		return Base + (Address - Modules[i].BaseAddress);
	}

	return 0;
}

bool __fastcall UtilityHandler::CompareBytes(BYTE* GameData, BYTE* Pattern, int Size)
{
	for (int i = 0; i < Size; ++i)
	{
		if (Pattern[i] == 0x00 && i < Size - 1)
			continue;

		if (Pattern[i] != GameData[i])
			break;

		if (i >= Size - 1)
			return true;
	}

	return false;
}

DWORD __fastcall UtilityHandler::FindPattern(char* szModule, char* szPattern, bool RetrieveAddress)
{
	ModuleInfo* Module = GetModule(szModule);

	if (!Module)
		return 0;

	char Pattern[128];
	strcpy_s(Pattern, szPattern);

	ReplaceString(Pattern, " ", "");
	ReplaceString(Pattern, "?", "00");

	DWORD dwBase = Module->BaseAddress;
	DWORD dwSize = Module->Size;
	BYTE* GameData = (BYTE*)dwBase;
	
	int PatternLength = strlen(Pattern) / 2;
	BYTE* bPattern = new BYTE[PatternLength];

	for (int i = 0, x = 0; i < PatternLength; ++i, x += 2)
	{
		char szTmp[4];
		sprintf_s(szTmp, "%c%c", Pattern[x], Pattern[x + 1]);
		bPattern[i] = (BYTE)strtoul(szTmp, 0, 16);
	}

	for (; (DWORD)GameData < dwBase + (dwSize - PatternLength); ++GameData)
	{
		for (int i = 0; i < PatternLength; ++i)
		{
			if (bPattern[i] == 0x00 && i < PatternLength - 1)
				continue;

			if (bPattern[i] != GameData[i])
				break;

			if (i >= PatternLength - 1)
			{
				DWORD dwRet = (DWORD)GameData;

				if (RetrieveAddress)
				{
					DWORD TmpAddr = 0;
					DWORD OpcodeLength = oplen(GameData);
					if (OpcodeLength == 0x5) TmpAddr = 0x1;
					if (OpcodeLength == 0x6) TmpAddr = 0x2;
					if (OpcodeLength > 0x6) TmpAddr = 0x3;

					if (TmpAddr) dwRet = *(PDWORD)(dwRet + TmpAddr);
				}

				return dwRet;
			}
		}
	}

	return 0;
}
// ===================================================================================