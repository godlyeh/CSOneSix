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
	void FillRGBA(int x, int y, int w, int h, color_t color);
	void LineRect(int x, int y, int w, int h, int lw, color_t color);
	void DepthFrame(int x, int y, int w, int h);
	void DrawWindow(char* Title, int x, int y, int w, int h, color_t color);
};