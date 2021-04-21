#include "DXUT.h"
#include "Renderer.h"

bool Renderer::Comp(Node* a, Node* b)
{
	return a->layer < b->layer;
}

void Renderer::SortRenderer()
{
	nodelist.sort(Comp);
}

void Renderer::DeleteObjects()
{
	for (auto& it : objectlist)
		delete it;
	objectlist.clear();
	nodelist.clear();
}

void Renderer::AddRender(Node* n)
{
	if (find(nodelist.begin(), nodelist.end(), n) != nodelist.end())
		return;
	nodelist.push_back(n);
}

void Renderer::AddObject(Node* n)
{
	if (find(objectlist.begin(), objectlist.end(), n) != objectlist.end())
		return;
	objectlist.push_back(n);
}

void Renderer::DeleteRender(Node* n)
{
	nodelist.remove(n);
}

void Renderer::Render()
{
	SortRenderer();
	for (auto& it : nodelist)
	{
		it->Update();
		it->Render();
	}
}
