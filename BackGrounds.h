#pragma once
#include "Sprite.h"
#include "System.h"
#include "Scene.h"

class BackGrounds
{
private:
	Scene* newScene = nullptr;

	Sprite* background[2];
	Sprite* tile[2];
	Sprite* WhiteScreen;

	bool bScene = false;
public:
	void BackGroundInit();
	void BackGroudUpdate();
	void ChangeScene(Scene* s);
};

