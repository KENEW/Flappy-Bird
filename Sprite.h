#pragma once

#include "Node.h"
#include "Director.h"
#include "Texture.h"
#include "Singleton.h"
#include "Renderer.h"
#include "Time.h"

class Sprite : public Node
{
public:
	Sprite();
	Sprite(wstring path, vec2 pos = { 0,0 }, vec2 s = { 1,1 }, vec2 p = { 0.5,0.5 }, int l = 0, bool is = false);

	virtual ~Sprite();

	Texture* texture = nullptr;

	void SetTexture(wstring path);
	void Render() override;
	void ChangeLayer(const UINT& _layer);
	RECT GetRect();

	float GetDistance(vec2 target);
	float GetAngle(vec2 target);
	void RotationMove(float speed);

	float RotationLerp(float start, float end, float amount);
	float Lerp(float start, float end, float amount);

	bool Animation(wstring path, int f, float t);
	int frame = 0;
	float tick = 0;

	bool isMouse();
};

