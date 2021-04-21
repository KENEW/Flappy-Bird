#include "DXUT.h"
#include "Camera.h"

void Camera::CameraInit()
{
	D3DXMatrixIdentity(&IM);
	camPos = { SCW / 2, SCH / 2 };
	camSize = 1;
	camRot = 0;
}

void Camera::CameraUpdate()
{
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, -camPos.x, -camPos.y, 0);
	
	D3DXMATRIX rot;
	D3DXMatrixRotationZ(&rot, camRot);

	VM = trans * rot;
	
	D3DXMatrixOrthoLH(&OM, SCW * camSize, -SCH * camSize, 0, 1);

	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &OM);
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &IM);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &VM);
}
