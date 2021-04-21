#include "DXUT.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Pipe.h"
#include "Sound.h"
#include "Player.h"
#include "Time.h"

/* 플래피버드 모작 - https://github.com/kenew */

void GameScene::Init()
{
	mciSendString(L"open res/Sound/GameBGM.mp3 type mpegvideo alias BGM", 0, 0, 0);
	mciSendString(L"play BGM notify repeat",0,0,0);

	background.BackGroundInit();

	font_invin = new Font(L"Arial", 2.0f, 900, { 100, 0 }, Color(1, 1, 1, 0));
	font_invin->layer = 1000;
	font_invin->SetString("무적모드 ON");
	
	PlayerManager::GetIns()->CreatePlayer();
	PlayerManager::GetIns()->player->position.x = SCW / 3.5;

	PipeManager::GetIns()->CreatePipe();
	System::GetIns()->score = 0;
	System::GetIns()->randomizeColor();

	getReady = new Sprite(L"bg_ready.png", { SCW / 2, SCH / 4 }, { 1,1 }, { 0.5,0.5 }, 10);
	tutorial = new Sprite(L"bg_tap.png", { SCW / 2, SCH / 1.75 }, { 1.5,1.5 }, { 0.5,0.5 }, 10);
	btnMenu = new Sprite(L"bg_button.png", { SCW / 2, SCH / 1.25 }, { 1.75,1.75 }, { 0.5,0.5 }, 100);
	btnMenu->color.a = -5.0f; //Player respawn button fade alpha init

	for (int i = 0; i < 5; i++)
	{
		spr_score[i] = new Sprite(L"0.png", { SCW / 2 - 90 + ((float)i * 45), 100 }, { 0.75, 0.8 }, { 0.5, 0.5 }, 40);
		spr_score[i]->tag = "score";
		spr_score[i]->visible = false;
	}

	SetvisibleFont(false);
}

void GameScene::Update()
{
	background.BackGroudUpdate();

	if (Director::GetIns()->OnMouseDown() || DXUTWasKeyPressed(VK_SPACE) || DXUTWasKeyPressed(VK_UP))
	{
		if (System::GetIns()->gamestate == GAME_ST::READY)
		{
			SetvisibleFont(true);
			System::GetIns()->gamestate = GAME_ST::PLAYING;
		}

		start = true;
		PlayerManager::GetIns()->player->Jump();
	}

	if (start)
	{
		getReady->color.a -= Time::deltaTime * 2;
		tutorial->color.a -= Time::deltaTime * 2;

		tickCreate += Time::deltaTime;

		if (tickCreate > 1.75f)
		{
			tickCreate = 0;
			PipeManager::GetIns()->SpawnPipe((rand() % 325) - 260);
		}

		if(!System::GetIns()->invin)
		{
			PipeManager::GetIns()->CollisionPipe();
		}

		if (System::GetIns()->gamestate == GAME_ST::GAMEOVER)
		{
			btnMenu->color.a += Time::deltaTime * 3;
		}

		char buff[255];
		memset(buff, '\0', 255);
		sprintf(buff, "%05d", System::GetIns()->score);

		for (int i = 0; i < 5; i++)
		{
			char c = buff[i];
			int n = atoi(&c);
			spr_score[i]->SetTexture(to_wstring(n) + L".png");
			spr_score[i]->visible = true;
		}
	}
	if (((Director::GetIns()->OnMouseDown() && btnMenu->isMouse()) || DXUTWasKeyPressed(VK_SPACE) || DXUTWasKeyPressed(VK_UP)) && btnMenu->color.a >= 1 && start)
	{
		start = false;
		Sound::GetIns()->playSonud(L"click");
		background.ChangeScene(new MenuScene);
		return;
	}

	//Game speed Key
	if (DXUTWasKeyPressed('1')) Time::scaleTime = 0.5f;
	if (DXUTWasKeyPressed('2')) Time::scaleTime = 1;
	if (DXUTWasKeyPressed('3')) Time::scaleTime = 1.5;
	if (DXUTWasKeyPressed('4')) Time::scaleTime = 2;

	//Game god mod
	if (DXUTWasKeyPressed('A'))
	{
		System::GetIns()->invin = !System::GetIns()->invin;
		font_invin->color.a = System::GetIns()->invin;
	}
}
void GameScene::Exit()
{
	PipeManager::GetIns()->DeletePipe();
	Scene::Exit();
}
