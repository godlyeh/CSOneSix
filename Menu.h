// ===================================================================================
// Variables
//typedef char MenuValue[8][32];

enum eEntryType : int
{
	ENTRY_INTEGER,
	ENTRY_FLOAT
};

typedef struct
{
	char Name[64];
	char* Value;
	int SubItem;
	bool IsVariable;
	eEntryType Type;
	void* pVariable;
	float Step, Min, Max;
}menuentry_t;
// ===================================================================================


// ===================================================================================
// Menu Helper
namespace Menu
{
	// Variables
	static bool MenuActive = false;
	static int MenuIndex = 0;

	// Funcs
	void FillMenuArray();
	void DrawMenu(color_t color, color_t selection);
	bool HandleKeys(int keynum);
	bool RegisterEntry(char* Name, int* pVariable, int SubItem = 0);
	void RegisterEntry(char* Name, eEntryType Type, void* pVariable, float Step, float Min, float Max, char* CustomValue[32] = NULL, int SubItem = 1);
	void RegisterEntry(char* Name, void* pVariable, float Step = 1, char CustomValue[][32] = NULL, int SubItem = 1);

	// Array
	static std::vector<menuentry_t> MenuStorage;
}

// ===================================================================================