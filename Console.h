// ===================================================================================
// Console info
typedef struct
{
	std::string Line;
}console_entry_t;

typedef struct
{
	char Name[64];
	void (__cdecl* Function)(std::string ConsoleCommand);
}console_cmd_t;

#define CON_ARG_INFINITE -1
#define ADD_CON_CMD(name) Console::AddCommand(#name, ConFunc_##name);
// ===================================================================================


// ===================================================================================
// Console handler
namespace Console
{
	// Variables
	static bool ConsoleActive = false;
	static std::string EditLine;
	static int EditPos = 0;

	// Funcs
	void AddCommand(char* CommandName, void(__cdecl* Function)(std::string ConsoleCommand));
	bool ShiftKeyHeld();
	bool CapslockActive();
	bool HandleKeys(int keynum);

	void InitializeDefaultCommands();

	void DrawConsole(color_t color);
	void Add(const char* Text, ...);
	void Parse(const std::string& Text);
	void Error(const char* ErrorMsg, ...);

	// Array
	static std::vector<console_cmd_t> ConsoleCmdStorage;
	static std::vector<console_entry_t> ConsoleStorage;
}

static char g_pszConsoleKeys[256][16] =
{
	"", // 0
	"", // 1
	"", // 2
	"", // 3
	"", // 4
	"", // 5
	"", // 6
	"", // 7
	"", // 8
	"TAB", // 9
	"", // 10
	"", // 11
	"", // 12
	"ENTER", // 13
	"", // 14
	"", // 15
	"", // 16
	"", // 17
	"", // 18
	"", // 19
	"", // 20
	"", // 21
	"", // 22
	"", // 23
	"", // 24
	"", // 25
	"", // 26
	"ESCAPE", // 27
	"", // 28
	"", // 29
	"", // 30
	"", // 31
	" ", // 32 - Space
	"", // 33
	"", // 34
	"", // 35
	"", // 36
	"", // 37
	"", // 38
	"", // 39
	"", // 40
	"", // 41
	"", // 42
	"", // 43
	",", // 44
	"+", // 45
	".", // 46
	"-", // 47
	"", // 48
	"1", // 49
	"2", // 50
	"3", // 51
	"4", // 52
	"5", // 53
	"6", // 54
	"7", // 55
	"8", // 56
	"9", // 57
	"0", // 58
	"", // 59
	"", // 60
	"\\", // 61
	"", // 62
	"", // 63
	"", // 64
	"", // 65
	"", // 66
	"", // 67
	"", // 68
	"", // 69
	"", // 70
	"", // 71
	"", // 72
	"", // 73
	"", // 74
	"", // 75
	"", // 76
	"", // 77
	"", // 78
	"", // 79
	"", // 80
	"", // 81
	"", // 82
	"", // 83
	"", // 84
	"", // 85
	"", // 86
	"", // 87
	"", // 88
	"", // 89
	"", // 90
	"", // 91
	"'", // 92
	"�", // 93
	"", // 94
	"", // 95
	"|", // 96
	"a", // 97
	"b", // 98
	"c", // 99
	"d", // 100
	"e", // 101
	"f", // 102
	"g", // 103
	"h", // 104
	"i", // 105
	"j", // 106
	"k", // 107
	"l", // 108
	"m", // 109
	"n", // 110
	"o", // 111
	"p", // 112
	"q", // 113
	"r", // 114
	"s", // 115
	"t", // 116
	"u", // 117
	"v", // 118
	"w", // 119
	"x", // 120
	"y", // 121
	"z", // 122
	"", // 123
	"", // 124
	"", // 125
	"", // 126
	"BACKSPACE", // 127
	"UPARROW", // 128
	"DOWNARROW", // 129
	"LEFTARROW", // 130
	"RIGHTARROW", // 131
	"ALT", // 132
	"CTRL", // 133
	"SHIFT", // 134
	"F1", // 135
	"F2", // 136
	"F3", // 137
	"F4", // 138
	"F5", // 139
	"F6", // 140
	"F7", // 141
	"F8", // 142
	"F9", // 143
	"F10", // 144
	"F11", // 145
	"F12", // 146
	"INSERT", // 147
	"DELETE", // 148
	"PAGEDOWN", // 149
	"PAGEUP", // 150
	"HOME", // 151
	"END", // 152
	"", // 153
	"", // 154
	"", // 155
	"", // 156
	"", // 157
	"", // 158
	"", // 159
	"NUMPAD7", // 160
	"NUMPAD8", // 161
	"NUMPAD9", // 162
	"NUMPAD4", // 163
	"NUMPAD5", // 164
	"NUMPAD6", // 165
	"NUMPAD1", // 166
	"NUMPAD2", // 167
	"NUMPAD3", // 168
	"NUMPAD_ENTER", // 169
	"NUMPAD0", // 170
	",", // 171
	"/", // 172
	"-", // 173
	"+", // 174
	"CAPSLOCK", // 175
	"", // 176
	"", // 177
	"", // 178
	"", // 179
	"", // 180
	"", // 181
	"", // 182
	"", // 183
	"", // 184
	"", // 185
	"", // 186
	"", // 187
	"", // 188
	"", // 189
	"", // 190
	"", // 191
	"", // 192
	"", // 193
	"", // 194
	"", // 195
	"", // 196
	"", // 197
	"", // 198
	"", // 199
	"", // 200
	"", // 201
	"", // 202
	"JOY1", // 203
	"JOY2", // 204
	"JOY3", // 205
	"JOY4", // 206
	"AUX1", // 207
	"AUX2", // 208
	"AUX3", // 209
	"AUX4", // 210
	"AUX5", // 211
	"AUX6", // 212
	"AUX7", // 213
	"AUX8", // 214
	"AUX9", // 215
	"JOY10", // 216
	"JOY11", // 217
	"JOY12", // 218
	"JOY13", // 219
	"JOY14", // 220
	"JOY15", // 221
	"JOY16", // 222
	"JOY17", // 223
	"JOY18", // 224
	"JOY19", // 225
	"JOY20", // 226
	"JOY21", // 227
	"JOY22", // 228
	"JOY23", // 229
	"JOY24", // 230
	"JOY25", // 231
	"JOY26", // 232
	"JOY27", // 233
	"JOY28", // 234
	"JOY29", // 235
	"AUX30", // 236
	"AUX31", // 237
	"AUX32", // 238
	"MWHEELDOWN", // 239
	"MWHEELUP", // 240
	"MOUSE1", // 241
	"MOUSE2", // 242
	"MOUSE3", // 243
	"MOUSE4", // 244
	"MOUSE5", // 245
	"", // 246
	"", // 247
	"", // 248
	"", // 249
	"", // 250
	"", // 251
	"", // 252
	"", // 253
	"", // 254
	"PAUSE" // 255
};

static char g_pszConsoleShiftKeys[256][16] =
{
	"", // 0
	"", // 1
	"", // 2
	"", // 3
	"", // 4
	"", // 5
	"", // 6
	"", // 7
	"", // 8
	"TAB", // 9
	"", // 10
	"", // 11
	"", // 12
	"ENTER", // 13
	"", // 14
	"", // 15
	"", // 16
	"", // 17
	"", // 18
	"", // 19
	"", // 20
	"", // 21
	"", // 22
	"", // 23
	"", // 24
	"", // 25
	"", // 26
	"ESCAPE", // 27
	"", // 28
	"", // 29
	"", // 30
	"", // 31
	" ", // 32 - Space
	"", // 33
	"", // 34
	"", // 35
	"", // 36
	"", // 37
	"", // 38
	"", // 39
	"", // 40
	"", // 41
	"", // 42
	"", // 43
	";", // 44
	"?", // 45
	":", // 46
	"_", // 47
	"", // 48
	"!", // 49
	"""", // 50
	"#", // 51
	"�", // 52
	"%", // 53
	"&", // 54
	"/", // 55
	"(", // 56
	")", // 57
	"=", // 58
	"", // 59
	"", // 60
	"`", // 61
	"", // 62
	"", // 63
	"", // 64
	"", // 65
	"", // 66
	"", // 67
	"", // 68
	"", // 69
	"", // 70
	"", // 71
	"", // 72
	"", // 73
	"", // 74
	"", // 75
	"", // 76
	"", // 77
	"", // 78
	"", // 79
	"", // 80
	"", // 81
	"", // 82
	"", // 83
	"", // 84
	"", // 85
	"", // 86
	"", // 87
	"", // 88
	"", // 89
	"", // 90
	"", // 91
	"*", // 92
	"^", // 93
	"", // 94
	"", // 95
	"�", // 96
	"A", // 97
	"B", // 98
	"C", // 99
	"D", // 100
	"E", // 101
	"F", // 102
	"G", // 103
	"H", // 104
	"I", // 105
	"J", // 106
	"K", // 107
	"L", // 108
	"M", // 109
	"N", // 110
	"O", // 111
	"P", // 112
	"Q", // 113
	"R", // 114
	"S", // 115
	"T", // 116
	"U", // 117
	"V", // 118
	"W", // 119
	"X", // 120
	"Y", // 121
	"Z", // 122
	"", // 123
	"", // 124
	"", // 125
	"", // 126
	"BACKSPACE", // 127
	"UPARROW", // 128
	"DOWNARROW", // 129
	"LEFTARROW", // 130
	"RIGHTARROW", // 131
	"ALT", // 132
	"CTRL", // 133
	"SHIFT", // 134
	"F1", // 135
	"F2", // 136
	"F3", // 137
	"F4", // 138
	"F5", // 139
	"F6", // 140
	"F7", // 141
	"F8", // 142
	"F9", // 143
	"F10", // 144
	"F11", // 145
	"F12", // 146
	"INSERT", // 147
	"DELETE", // 148
	"PAGEDOWN", // 149
	"PAGEUP", // 150
	"HOME", // 151
	"END", // 152
	"", // 153
	"", // 154
	"", // 155
	"", // 156
	"", // 157
	"", // 158
	"", // 159
	"NUMPAD7", // 160
	"NUMPAD8", // 161
	"NUMPAD9", // 162
	"NUMPAD4", // 163
	"NUMPAD5", // 164
	"NUMPAD6", // 165
	"NUMPAD1", // 166
	"NUMPAD2", // 167
	"NUMPAD3", // 168
	"NUMPAD_ENTER", // 169
	"NUMPAD0", // 170
	",", // 171
	"/", // 172
	"-", // 173
	"+", // 174
	"CAPSLOCK", // 175
	"", // 176
	"", // 177
	"", // 178
	"", // 179
	"", // 180
	"", // 181
	"", // 182
	"", // 183
	"", // 184
	"", // 185
	"", // 186
	"", // 187
	"", // 188
	"", // 189
	"", // 190
	"", // 191
	"", // 192
	"", // 193
	"", // 194
	"", // 195
	"", // 196
	"", // 197
	"", // 198
	"", // 199
	"", // 200
	"", // 201
	"", // 202
	"JOY1", // 203
	"JOY2", // 204
	"JOY3", // 205
	"JOY4", // 206
	"AUX1", // 207
	"AUX2", // 208
	"AUX3", // 209
	"AUX4", // 210
	"AUX5", // 211
	"AUX6", // 212
	"AUX7", // 213
	"AUX8", // 214
	"AUX9", // 215
	"JOY10", // 216
	"JOY11", // 217
	"JOY12", // 218
	"JOY13", // 219
	"JOY14", // 220
	"JOY15", // 221
	"JOY16", // 222
	"JOY17", // 223
	"JOY18", // 224
	"JOY19", // 225
	"JOY20", // 226
	"JOY21", // 227
	"JOY22", // 228
	"JOY23", // 229
	"JOY24", // 230
	"JOY25", // 231
	"JOY26", // 232
	"JOY27", // 233
	"JOY28", // 234
	"JOY29", // 235
	"AUX30", // 236
	"AUX31", // 237
	"AUX32", // 238
	"MWHEELDOWN", // 239
	"MWHEELUP", // 240
	"MOUSE1", // 241
	"MOUSE2", // 242
	"MOUSE3", // 243
	"MOUSE4", // 244
	"MOUSE5", // 245
	"", // 246
	"", // 247
	"", // 248
	"", // 249
	"", // 250
	"", // 251
	"", // 252
	"", // 253
	"", // 254
	"PAUSE" // 255
};
// ===================================================================================