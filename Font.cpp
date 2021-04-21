#include "DXUT.h"
#include "Font.h"

Font::Font()
{
	memset(buff, '\0', sizeof(buff));
	D3DXCreateFont(DXUTGetD3D9Device(), 20, 0, 700, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, L"Arial", &font);
	Renderer::GetIns()->AddRender(this);
}

Font::Font(LPCWSTR path, float scale, float weight, vec2 pos, Color co)
{
	position = pos;
	color = co;
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * scale, 0, weight, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, path, &font);
	Renderer::GetIns()->AddRender(this);
}

void Font::SetString(char* string)
{
	sprintf(buff, string);
}

void Font::Render()
{
	if (!visible) return;
	if (font == nullptr) return;

	RECT r;
	if (isUI)
	{
		r = { (long)position.x, (long)position.y, 0, 0 };
	}
	else
	{
		r = { (long)(position.x - (Camera::GetIns()->camPos.x - SCW / 2)) ,
		(long)(position.y - (Camera::GetIns()->camPos.y - SCH / 2)) , 0, 0 };
	}
	font->DrawTextA(nullptr, buff, -1, &r, DT_NOCLIP, color);
}

void Font::CreateMyFont(float scale, float weight, LPCWSTR path)
{
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * scale, 0, weight, 1, 0, 1, 0, 0, 0 | FF_DONTCARE, path, &font);
}
