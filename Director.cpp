#include "DXUT.h"
#include "Director.h"

void Director::DirectorInit()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
	Camera::GetIns()->CameraInit();
	curScene = nullptr;
}

void Director::DirectorUpdate()
{
	if (curScene != nullptr)
		curScene->Update();
	Camera::GetIns()->CameraUpdate();

	if (nClick == 1) nClick = 2;
	if (nClick == 3) nClick = 0;

	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);
}

void Director::ChangeScene(Scene* newScene)
{
	if (curScene != nullptr)
		curScene->Exit();

	curScene = newScene;
	curScene->Init();
}

bool Director::OnMouseDown()
{
	if (nClick == 1)
		return true;
	return false;
}

bool Director::OnMouse()
{
	if (nClick == 2)
		return true;
	return false;
}

bool Director::OnMouseUp()
{
	if (nClick == 3)
		return true;
	return false;
}

vec2 Director::GetMousePos()
{
	return vec2((float)p.x, (float)p.y);
}
