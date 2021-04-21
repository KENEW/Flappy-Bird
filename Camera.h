#pragma once

#include "Singleton.h"


class Camera : public Singleton<Camera>
{
public:
	D3DXMATRIX OM;
	D3DXMATRIX IM;
	D3DXMATRIX VM;

	vec2 camPos;
	float camSize;
	float camRot;

	void CameraInit();
	void CameraUpdate();
};

