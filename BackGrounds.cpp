#include "DXUT.h"
#include "BackGrounds.h"
#include "System.h"

void BackGrounds::BackGroundInit()
{
	bScene = false;
	WhiteScreen = new Sprite(L"WhiteScreen.png", { 0,0 }, { 1,1 }, { 0,0 }, 10000, true);
	System::GetIns()->SetWhiteScreen(WhiteScreen);

	for (int i = 0; i < 2; ++i)
	{
		background[i] = new Sprite(L"bg_noon.bmp", { (float)i * SCW, 0 }, { 1, 1 }, { 0, 0 });
		tile[i] = new Sprite(L"bg_tile.bmp", { (float)i * (215 * 3), 920 }, { 3, 1.75 }, { 0, 1 }, 20);
	}
}

void BackGrounds::BackGroudUpdate()
{
	if (System::GetIns()->gamestate != GAME_ST::GAMEOVER)
	{
		for (int i = 0; i < 2; ++i)
		{
			tile[i]->position.x -= Time::deltaTime * System::GetIns()->scrollSpeed;

			if (tile[i]->position.x <= -(215 * 3))
			{
				tile[i]->position.x += (215 * 3) * 2;
			}
		}
	}
	if (bScene)
	{
		if (WhiteScreen->color.a <= 1)
		{
			WhiteScreen->color.a += Time::deltaTime * 3.0f;
		}
		else
		{
			System::GetIns()->gamestate = GAME_ST::READY;
			Director::GetIns()->ChangeScene(newScene);
			return;
		}
	}
	else if (WhiteScreen->color.a > 0)
	{
		WhiteScreen->color.a -= Time::deltaTime * 3;
	}
}

void BackGrounds::ChangeScene(Scene* s)
{
	bScene = true;
	newScene = s;
}
