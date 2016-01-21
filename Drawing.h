typedef struct { int r, g, b, a; } color_t;

color_t rgb(int r, int g, int b);
color_t rgb(int r, int g, int b, int a);

namespace g_Draw
{
	void DrawString(bool Center, int x, int y, color_t color, char* Text, ...);
	int GetStringWidth(char* Text, ...);
	int GetStringHeight();
	void FillRGBA(int x, int y, int w, int h, color_t color);
};