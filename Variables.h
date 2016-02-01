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
	// Player ESP
	static int Name = 1;
	static int WeaponName = 1;
	static int Distance = 1;
	static float PlayerHeightCorrection = 0.0f;

	// Weapon ESP
	static int WeaponGroundName = 1;
	static int DistanceGround = 1;
	static float GroundHeightCorrection = 0.0f;

	// Entity ESP
	static int Hostage = 1;
	static int DistanceEntity = 1;
	static float EntityHeightCorrection = 0.0f;

	// HUD
	//static int MaxHudMessages = 5;

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