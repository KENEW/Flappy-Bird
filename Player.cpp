#include "DXUT.h"
#include "Player.h"
#include "System.h"
#include "Sound.h"
#include "Time.h"

Player::Player()
{
	body = new Sprite(L"body (1).png");
	body->color = System::GetIns()->playerColor;
	body->SetParent(this);
	body->layer = 12;

	gameover = new Sprite(L"bg_gameOver.png", { SCW / 2, SCH / 4 }, { 1.25, 1 }, { 0.5, 0.5 }, 100, true);
	gameover->color.a = -2;

	blackscreen = new Sprite(L"blackscreen.png", { 0,0 }, { 1,1 }, { 0,0 }, 50, true);
	blackscreen->color.a = 0;

	HighScore = new Font(L"VCR OSD Mono", 2, 350, { SCW / 2 - 120, SCH / 2.3 });
	HighScore->layer = 100;
	HighScore->color.a = -4;

	curScore = new Font(L"VCR OSD Mono", 2, 350, { SCW / 2 - 120, SCH / 1.65 });
	curScore->layer = 100;
	curScore->SetString("");
	curScore->color.a = -6;

	New = new Sprite(L"new_record.png", { SCW / 2 + 77 ,SCH / 2 + 80 }, { 1, 1 }, { 0.5,0.5 }, 60);
	New->color.a = -6;
	New->visible = false;

	position = { SCW / 2, SCH / 2.25 };
	layer = 11;
	SetTexture(L"bird1 (1).png");
}

void Player::Update()
{
	if (System::GetIns()->gamestate != GAME_ST::GAMEOVER) 
	{
		Animation(L"bird1", 3, 0.1f);
		body->Animation(L"body", 3, 0.1f);
	}
	if (System::GetIns()->gamestate != GAME_ST::READY)
	{
		velocity.y += 1500 * Time::deltaTime;
		rotation = RotationLerp(rotation, GetAngle(vEye), Time::deltaTime * 12);
	}
	if (System::GetIns()->gamestate == GAME_ST::READY)
	{
		tickTurn += Time::deltaTime;
		if (tickTurn >= 0.3f)
		{
			tickTurn = 0.0f;
			turn = !turn;
		}
		position.y += Time::deltaTime * 50 * (turn ? 1 : -1);
	}
	else if (System::GetIns()->gamestate == GAME_ST::PLAYING)
	{
		position += velocity * Time::deltaTime;
		vEye = vec2(velocity.x + 800, velocity.y);

		if (position.y < 0) position.y = 0;
		if (position.y > 694.75)
		{
			position.y = 694.75;
			if (!System::GetIns()->invin)
			{
				Sound::GetIns()->playSonud(L"set");
				System::GetIns()->gamestate = GAME_ST::GAMEOVER;
				System::GetIns()->whitescreen->color = Color(1, 1, 1, 1);
			}
		}
	}
	else if (System::GetIns()->gamestate == GAME_ST::GAMEOVER)
	{
		mciSendString(L"stop BGM", 0, 0, 0);
		if (System::GetIns()->score > System::GetIns()->highScore)
		{
			New->visible = true;
			System::GetIns()->highScore = System::GetIns()->score;
		}
		position.y += velocity.y * Time::deltaTime;
		vEye.x = position.x + 10;
		vEye.y += 1500 * Time::deltaTime;

		gameover->color.a += Time::deltaTime * 3;
		HighScore->color.a += Time::deltaTime * 3;
		curScore->color.a += Time::deltaTime * 3;
		New->color.a += Time::deltaTime * 3;
		blackscreen->color.a = 0.5f;

		if (position.y > 694.75)
			position.y = 694.75;

		char buff[255];
		sprintf(buff, "HIGH SCORE\n    %02d", System::GetIns()->highScore);
		HighScore->SetString(buff);
		sprintf(buff, "SCORE : %d", System::GetIns()->score);
		curScore->SetString(buff);
	}
}

void Player::Jump()
{
	if (System::GetIns()->gamestate != GAME_ST::PLAYING) 
	{
		return;
	}

	Sound::GetIns()->playSonud(L"jump");
	velocity.y = -600;
}
