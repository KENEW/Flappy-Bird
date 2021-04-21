#pragma once
#include "Singleton.h"
#include "Time.h"
#include "Sprite.h"

class System : public Singleton<System>
{
private:
	Color colorList[8] = {
		Color(1,0,0,1),
		Color(1,0.5,0,1),
		Color(1,1,0,1),
		Color(0,1,0,1),
		Color(0,0,1,1),
		Color(1,0,1,1),
		Color(0,0,0,1),
		Color(1,1,1,1) 
	};
	int colorindex = 0;
public:
	int highScore = 0;
	int score = 0;

	int gamestate = 0;
	float scrollSpeed = 200.0f;
	Color playerColor = colorList[rand() % 8];

	bool invin = false;

	Sprite* whitescreen;
	void SetWhiteScreen(Sprite* spr) { whitescreen = spr; };

	void randomizeColor() { playerColor = colorList[rand() % 8]; };
	void nextColor() { playerColor = colorList[colorindex++]; colorindex %= 8; };
};

