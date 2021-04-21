#pragma once

#include "Scene.h"
#include "Camera.h"

class Director : public Singleton<Director>
{
private:
	LPD3DXSPRITE sprite;
public:
	Scene* curScene;
	LPD3DXSPRITE GetSprite() {
		return sprite;
	}
	
	void DirectorInit();
	void DirectorUpdate();
	void ChangeScene(Scene* newScene);

	int nClick;
	bool OnMouseDown();
	bool OnMouse();
	bool OnMouseUp();

	POINT p;
	vec2 GetMousePos();
};