#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "System.h"
#include "Font.h"
#include "BackGrounds.h"

class GameScene : public Scene
{
public:
	BackGrounds background;
	
	Font* font_invin;

	Sprite* getReady;
	Sprite* tutorial;
	Sprite* btnMenu;

	Sprite* spr_score[5];

	bool start = false;
	float tickCreate = 2;

	void SetvisibleFont(bool b) 
	{
		for (int i = 0; i < 5; ++i)
		{
			spr_score[i]->visible = b;
		}
	}

	virtual void Init();
	virtual void Update();
	virtual void Exit();
};

