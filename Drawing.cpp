#include "Main.h"

void g_Draw::DrawString(bool Center, int x, int y, color_t color, char* Text, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	if (Center) x -= GetStringWidth(szBuffer) / 2;
	g_oEngine.pfnDrawSetTextColor(((float)color.r / 255.0f), ((float)color.g / 255.0f), ((float)color.b / 255.0f));
	g_oEngine.pfnDrawConsoleString(x, y, szBuffer);
}

int g_Draw::GetStringWidth(char* Text, ...)
{
	int w, h;
	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	g_oEngine.pfnDrawConsoleStringLen(szBuffer, &w, &h);
	return w;
}

int g_Draw::GetStringHeight()
{
	int w, h;
	g_oEngine.pfnDrawConsoleStringLen("Aj", &w, &h);
	return h;
}

void g_Draw::FillRGBA(int x, int y, int w, int h, color_t color)
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