#include "DXUT.h"
#include "Pipe.h"
#include "System.h"
#include "Player.h"
#include "Sound.h"

Pipe::Pipe()
{
	position = { -9999,-9999 };
	Renderer::GetIns()->AddRender(this);
	visible = false;

	topPipe = new Sprite(L"bg_pillarUp.png", { 0,0 }, { 1,1 }, { 0.5,1.3f }, 10);
	bottomPipe = new Sprite(L"bg_pillarDown.png", { 0,0 }, { 1,1 }, { 0.5,-0.3f }, 10);
	topPipe->SetParent(this);
	bottomPipe->SetParent(this);
}

void Pipe::Create()
{
	isCollision = false;
	position = { SCW + 300, SCH / 2 + heigth };
	visible = true;
}

void Pipe::Update()
{
	if (System::GetIns()->gamestate != GAME_ST::GAMEOVER)
	{
		position.x -= Time::deltaTime * System::GetIns()->scrollSpeed;
	}
	if (position.x < -300) 
	{
		Death();
	}

	RECT r;
	if (!isCollision)
	{
		if (IntersectRect(&r, &PlayerManager::GetIns()->player->GetRect(), &Rect()))
		{
			isCollision = true;
			System::GetIns()->score++;
			Sound::GetIns()->playSonud(L"record");
		}
	}
}

void Pipe::Death()
{
	position = { -9999,-9999 };
	visible = false;
}

RECT Pipe::Rect()
{
	RECT r;

	r.right = position.x + 10;
	r.left = position.x - 10;
	r.top = position.y - 2000;
	r.bottom = position.y + 2000;

	return r;
}

void PipeManager::SpawnPipe(float heigth)
{
	for (auto& it : pipelist)
	{
		if (!it->visible)
		{
			it->heigth = heigth;
			it->Create();
			break;
		}
	}
}

void PipeManager::CollisionPipe()
{
	if (System::GetIns()->gamestate != GAME_ST::PLAYING) return;

	for (auto& p : pipelist)
	{
		RECT r;
		if (IntersectRect(&r, &PlayerManager::GetIns()->player->GetRect(), &p->bottomPipe->GetRect()) ||
			IntersectRect(&r, &PlayerManager::GetIns()->player->GetRect(), &p->topPipe->GetRect()))
		{
			Sound::GetIns()->playSonud(L"set");
			System::GetIns()->gamestate = GAME_ST::GAMEOVER;
			PlayerManager::GetIns()->player->velocity = { 10,0 };
			System::GetIns()->whitescreen->color = Color(1, 1, 1, 1);
		}
	}
}
