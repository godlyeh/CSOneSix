// ===================================================================================
// Variables
enum eVariableType : int
{
	VAR_INTEGER,
	VAR_FLOAT
};

typedef struct
{
	char Name[64];
	eVariableType Type;
	void* pVariable;
	float Default, Min, Max;
}variable_t;
// ===================================================================================


// ===================================================================================
// Variable helper
namespace Variable
{
	// ESP
	static int Name = 1;
	static float HeightCorrection = 0.2f;

	// Funcs
	void Initialize();
	void Register(char* Name, eVariableType Type, void* pVariable, float Min, float Max);
	variable_t* GetVariable(const char* Name);
	void Save(char* FileName);
	void Load(char* FileName);

	// Array
	static std::vector<variable_t> VariableStorage;
}

// ===================================================================================