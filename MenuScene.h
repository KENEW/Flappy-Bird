#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "BackGrounds.h"
#include "System.h"

class MenuScene : public Scene
{
public:
	BackGrounds background;
	Sprite* btnStart;

	float tickTurn = 0.0f;
	bool turn = false;
	bool start = true;

	virtual void Init();
	virtual void Update();
	virtual void Exit();
};

