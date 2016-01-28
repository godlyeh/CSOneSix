// ===================================================================================
// Module info
typedef struct
{
	char Name[MAX_PATH];
	DWORD BaseAddress;
	DWORD Size;
}ModuleInfo;
// ===================================================================================


// ===================================================================================
// Utility class
class UtilityHandler
{
public:
	// String handling
	char *StringA(const char* Text, ...);
	void ReplaceString(char* Text, char* SearchText, char* TextToReplace);
	std::vector<std::string> &SplitString(const std::string &String, char c, std::vector<std::string> &Elements);
	std::vector<std::string> SplitString(const std::string &String, char c);
	std::string GetStringArg(const std::string &String, int Arg);

	// File handling
	bool FileExist(char* FileName);
	void Log(char* FileName, const char* Text, ...);
	void DeleteLog(char* FileName);

	// Module list
	ModuleInfo* GetModule(char *Module, DWORD dwBaseAddress = 0);
	void GenerateModuleList();

	// Memory handling
	THREADENTRY32* GetProcessThread();
	DWORD CalcModuleOffset(DWORD Address);
	bool __fastcall CompareBytes(BYTE* GameData, BYTE* Pattern, int Size);
	DWORD __fastcall FindPattern(char* szModule, char* szPattern, bool RetrieveAddress = true);

private:
	std::vector<ModuleInfo> Modules;
};

extern UtilityHandler* Utility;
// ===================================================================================


// ===================================================================================
// Defines
#define GET_VA_ARGS(text, buffer) va_list valist; \
								  va_start(valist, text); \
								  _vsnprintf_s(buffer, MAX_PATH, text, valist); \
							  	  va_end(valist);

#define HACKDIR(filename) Utility->StringA("%s%s", g_szHackDir, filename)
// ===================================================================================