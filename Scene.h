#pragma once

#include "Renderer.h"
#include "Singleton.h"

class Scene
{
public: 
	// vTable ( 버추얼 테이블 ) 공부해오기
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Exit();
};

