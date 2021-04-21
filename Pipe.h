#pragma once

#include "Sprite.h"
#include "Singleton.h"

class Pipe : public Sprite
{
public:
	explicit Pipe();

	Sprite* topPipe;
	Sprite* bottomPipe;

	float heigth = 0;
	bool isCollision = false;
	
	void Create();
	void Update() override;
	void Death();

	RECT Rect();
};

class PipeManager : public Singleton<PipeManager>
{
public:
	Pipe* pipe;
	list<Pipe*> pipelist;

	void CreatePipe() 
	{
		for (int i = 0; i < 5; ++i)
		{
			pipe = new Pipe();
			pipelist.push_back(pipe);
		}
	};
	void DeletePipe() 
	{ 
		pipelist.clear();
	};
	void SpawnPipe(float heigth);
	void CollisionPipe();
};

