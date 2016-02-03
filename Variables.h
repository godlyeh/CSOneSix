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
#define REG_INTEX(name) extern int name
#define REG_FLOATEX(name) extern float name

	// Aimbot
	REG_INTEX(Aimbot);
	REG_INTEX(AimPosition);
	REG_INTEX(AimDrawPosition);

	// Player ESP
	REG_INTEX(Name);
	REG_INTEX(WeaponName);
	REG_INTEX(Distance);
	REG_INTEX(Sequence);
	REG_INTEX(Box);
	REG_INTEX(Box_Width);
	REG_INTEX(Box_Height);
	REG_FLOATEX(PlayerHeightCorrection);

	// Weapon ESP
	REG_INTEX(WeaponGroundName);
	REG_INTEX(DistanceGround);
	REG_FLOATEX(GroundHeightCorrection);

	// Entity ESP
	REG_INTEX(Hostage);
	REG_INTEX(DistanceEntity);
	REG_FLOATEX(EntityHeightCorrection);

	// OpenGL
	REG_INTEX(Wallhack);
	REG_FLOATEX(Wallhack_Transparency);

	// HUD
	//static int MaxHudMessages = 5;

	// Funcs
	void Initialize();
	void Register(char* Name, eVariableType Type, void* pVariable, float Min, float Max);
	variable_t* GetVariable(const char* Name);
	variable_t* GetVariable(const void* pVariable);
	void Save(char* FileName);
	void Load(char* FileName);

	// Array
	static std::vector<variable_t> VariableStorage;
}

// ===================================================================================