typedef struct { int r, g, b, a; } color_t;

color_t rgb(int r, int g, int b);
color_t rgb(int r, int g, int b, int a);

namespace Draw
{
	void DrawString(bool Center, int x, int y, color_t color, char* Text, ...);
	void DrawString(bool Center, bool DrawBG, int x, int y, color_t color, char* Text, ...);
	void DrawString(bool Center, bool DrawBG, float* Pos, color_t color, char* Text, ...);
	int GetStringWidth(char* Text, ...);
	int GetStringHeight();
	void Line(int x1, int y1, int x2, int y2, color_t color, float lw = 1.0f);
	void FillRGBA(int x, int y, int w, int h, color_t color);
	void LineRect(int x, int y, int w, int h, int lw, color_t color);
	void DepthFrame(int x, int y, int w, int h);
	void DrawWindow(char* Title, int x, int y, int w, int h, color_t color);
	void DrawVectorLine(float *flSrc, float *flDestination, int lw, color_t color);
	void Draw3DBox(bool bIsPlayer, Vector vOrigin, Vector vMins, Vector vMaxs, float *flAngles, int lw, color_t color);
	void Draw3DBox(int EntityID, int lw, color_t color);
};