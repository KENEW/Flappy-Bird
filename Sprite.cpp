#include "DXUT.h"
#include "Sprite.h"

Sprite::Sprite()
{
	texture = nullptr;
}

Sprite::Sprite(wstring path, vec2 pos, vec2 s, vec2 p, int l, bool is)
{
	position = pos;
	scale = s;
	pivot = p;
	layer = l;
	isUI = is;
	SetTexture(path);
}

Sprite::~Sprite()
{
	if (texture != nullptr)
	{
		wcout  << "DELETED " << texture->path << endl;
	}
	Renderer::GetIns()->DeleteRender(this);
}

void Sprite::SetTexture(wstring path)
{
	texture = TextureManager::GetIns()->LoadTexture(path);
	SetRect(&imgRect, 0, 0, texture->info.Width, texture->info.Height);
	Renderer::GetIns()->AddRender(this);
}

void Sprite::Render()
{
	if (!visible) return;
	if (texture == nullptr) return;

	isUI ? Director::GetIns()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND) :
		Director::GetIns()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	Director::GetIns()->GetSprite()->SetTransform(&GetMatrix());
	vec3 centor;
	centor.x = texture->info.Width * pivot.x;
	centor.y = texture->info.Height * pivot.y;
	centor.z = 0;
	Director::GetIns()->GetSprite()->Draw(texture->texture, &imgRect, &centor, nullptr, color);
	Director::GetIns()->GetSprite()->End();
}

void Sprite::ChangeLayer(const UINT& _layer)
{
	layer = _layer;
	Renderer::GetIns()->SortRenderer();
}

RECT Sprite::GetRect()
{
	RECT r;
	vec2 pos = parent == nullptr ? position : position + parent->position;

	r.right = pos.x + ((collscale.x * texture->info.Width) * pivot.x * scale.x);
	r.left = pos.x - ((collscale.x * texture->info.Width) * (1 - pivot.x) * scale.x);
	r.top = pos.y - ((collscale.y * texture->info.Height) * (1 - pivot.y) * scale.y);
	r.bottom = pos.y + ((collscale.y * texture->info.Height) * pivot.y * scale.y);

	if (scale.x < 0)
	{
		float temp = r.right;
		r.right = r.left;
		r.left = temp;
	}
	if (scale.y < 0)
	{
		float temp = r.top;
		r.top = r.bottom;
		r.bottom = temp;
	}

	return r;
}

float Sprite::GetDistance(vec2 target)
{
	vec2 pos = target - position;
	return sqrt(pos.x * pos.x + pos.y * pos.y);
}

float Sprite::GetAngle(vec2 target)
{
	vec2 pos = target - position;
	return atan2(pos.y, pos.x);
}

void Sprite::RotationMove(float speed)
{
	position += vec2(cosf(rotation) * speed, sinf(rotation) * speed) * Time::deltaTime;
}

float Sprite::RotationLerp(float start, float end, float amount)
{
	if (fabs(start - end) >= D3DX_PI)
	{
		if (start > end) end += 2 * D3DX_PI;
		else start += 2 * D3DX_PI;
	}
	float value = Lerp(start, end, amount);
	if (value >= 0 && value <= D3DX_PI * 2)
		return value;
	return fmodf(value, D3DX_PI * 2);
}

float Sprite::Lerp(float start, float end, float amount)
{
	return start + (end - start) * amount;
}

bool Sprite::Animation(wstring path, int f, float t)
{
	tick += Time::deltaTime;
	if (tick > t)
	{
		frame++;
		if (frame > f)
		{
			frame = 0;
			return true;
		}
		tick = 0;
		SetTexture(path + L" (" + to_wstring(frame) + L").png");
	}
	return false;
}

bool Sprite::isMouse()
{
	if (!visible) return false;

	vec2 pos = Director::GetIns()->GetMousePos();
	if (GetRect().left < pos.x && GetRect().right > pos.x &&
		GetRect().top < pos.y && GetRect().bottom > pos.y)
		return true;
	return false;
}
