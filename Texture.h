#pragma once

#include "Singleton.h"

class Texture
{
public:
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture; 
	wstring path;
};

class TextureManager : public Singleton<TextureManager>
{
public:
	list<Texture*> texturelist;
	Texture* LoadTexture(wstring path);
};
