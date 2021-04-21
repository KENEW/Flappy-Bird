#include "DXUT.h"
#include "Scene.h"

void Scene::Exit()
{
	Renderer::GetIns()->DeleteObjects();
}
