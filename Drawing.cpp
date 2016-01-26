#include "Main.h"

void Draw::DrawString(bool Center, int x, int y, color_t color, char* Text, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	if (Center) x -= GetStringWidth(szBuffer) / 2;
	g_oEngine.pfnDrawSetTextColor(((float)color.r / 255.0f), ((float)color.g / 255.0f), ((float)color.b / 255.0f));
	g_oEngine.pfnDrawConsoleString(x, y, szBuffer);
}

void Draw::DrawString(bool Center, bool DrawBG, int x, int y, color_t color, char* Text, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	if (Center) x -= GetStringWidth(szBuffer) / 2; 
	if (DrawBG) FillRGBA(x - 2, y - 1, GetStringWidth(szBuffer) + 4, GetStringHeight() + 2, rgb(0, 0, 0, 128));
	g_oEngine.pfnDrawSetTextColor(((float)color.r / 255.0f), ((float)color.g / 255.0f), ((float)color.b / 255.0f));
	g_oEngine.pfnDrawConsoleString(x, y, szBuffer);
}

void Draw::DrawString(bool Center, bool DrawBG, float* Pos, color_t color, char* Text, ...)
{
	int x = (int)Pos[0];
	int y = (int)Pos[1];

	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	if (Center) x -= GetStringWidth(szBuffer) / 2;
	if (DrawBG) FillRGBA(x - 2, y - 1, GetStringWidth(szBuffer) + 4, GetStringHeight() + 2, rgb(0, 0, 0, 128));
	g_oEngine.pfnDrawSetTextColor(((float)color.r / 255.0f), ((float)color.g / 255.0f), ((float)color.b / 255.0f));
	g_oEngine.pfnDrawConsoleString(x, y, szBuffer);
}

int Draw::GetStringWidth(char* Text, ...)
{
	int w, h;
	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	g_oEngine.pfnDrawConsoleStringLen(szBuffer, &w, &h);
	return w;
}

int Draw::GetStringHeight()
{
	int w, h;
	g_oEngine.pfnDrawConsoleStringLen("Aj", &w, &h);
	return h;
}

void Draw::FillRGBA(int x, int y, int w, int h, color_t color)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(color.r, color.g, color.b, color.a);

	glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x + w, y);
		glVertex2i(x + w, y + h);
		glVertex2i(x, y + h);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Draw::LineRect(int x, int y, int w, int h, int lw, color_t color)
{
	FillRGBA(x - lw, y - lw, w + lw * 2, lw, color);
	FillRGBA(x - lw, y, lw, h, color);
	FillRGBA(x + w, y, lw, h, color);
	FillRGBA(x - lw, y + h, w + lw * 2, lw, color);
}

void Draw::DepthFrame(int x, int y, int w, int h)
{
	FillRGBA(x, y, w - 1, 1, rgb(0, 0, 0, 128));
	FillRGBA(x, y + 1, 1, h - 1, rgb(0, 0, 0, 128));
	FillRGBA(x + 1, y + h - 1, w - 1, 1, rgb(255, 255, 255, 128));
	FillRGBA(x + w - 1, y, 1, h - 1, rgb(255, 255, 255, 128));
}

void Draw::DrawWindow(char* Title, int x, int y, int w, int h, color_t color)
{
	if (Title != NULL)
	{
		int H = GetStringHeight() + 2;

		y -= (H + 5);

		FillRGBA(x, y, w, H, color);
		LineRect(x, y, w, H, 1, rgb(0, 0, 0, 128));
		DrawString(true, x + w / 2, y, rgb(255, 255, 255), Title);

		y += (H + 5);
	}

	FillRGBA(x, y, w, h, color);
	LineRect(x, y, w, h, 1, rgb(0, 0, 0, 128));
	DepthFrame(x, y, w, h);
}

color_t rgb(int r, int g, int b)
{
	color_t clrRet = { r, g, b, 255 };
	return clrRet;
}

color_t rgb(int r, int g, int b, int a)
{
	color_t clrRet = { r, g, b, a };
	return clrRet;
}