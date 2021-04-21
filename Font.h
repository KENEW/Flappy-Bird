#pragma once

#include "Node.h"
#include "Renderer.h"
#include "Camera.h"

class Font : public Node
{
public:
	Font();
	Font(LPCWSTR path, float scale = 1, float weight = 700, vec2 pos = {0,0}, Color co = Color(1,1,1,1));
	virtual ~Font() { Renderer::GetIns()->DeleteRender(this); font->Release();};

	LPD3DXFONT font;

	char buff[255];

	void SetString(char* string);
	void Render() override;
	void CreateMyFont(float scale, float weight, LPCWSTR path);
};

