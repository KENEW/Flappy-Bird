#pragma once

#include "Node.h"
#include "Singleton.h"


class Renderer : public Singleton<Renderer>
{
public:
	list<Node*> nodelist;
	list<Node*> objectlist;

	static bool Comp(Node* a, Node* b);

	void SortRenderer();
	void DeleteObjects();
	
	void AddRender(Node* n);
	void AddObject(Node* n);
	void DeleteRender(Node* n);
	void Render();
};

