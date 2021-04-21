#include "DXUT.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Player.h"
#include "Sound.h"

void MenuScene::Init()
{
	background.BackGroundInit();

	Sprite* title = new Sprite(L"bg_title.png", { SCW / 2, SCH / 3.25 }, { 1.25,1.25 }, { 0.5,0.5 }, 10);
	btnStart = new Sprite(L"bg_button.png", { SCW / 2, SCH / 1.5 }, { 1.75,1.75 }, { 0.5,0.5 }, 10);
	start = true;

	PlayerManager::GetIns()->CreatePlayer();
}

void MenuScene::Update()
{
	background.BackGroudUpdate();

	if ((Director::GetIns()->OnMouseDown() && btnStart->isMouse()) || DXUTWasKeyPressed(VK_SPACE) || DXUTWasKeyPressed(VK_UP) && start)
	{
		start = false;
		Sound::GetIns()->playSonud(L"click");
		background.ChangeScene(new GameScene);
	}

	if (Director::GetIns()->OnMouseDown()) 
	{
		if (PlayerManager::GetIns()->player->isMouse())
		{
			System::GetIns()->nextColor();
			PlayerManager::GetIns()->player->body->color = System::GetIns()->playerColor;
		}
	}
}

void MenuScene::Exit()
{
	Scene::Exit();
}