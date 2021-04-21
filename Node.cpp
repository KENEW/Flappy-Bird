#include "DXUT.h"
#include "Node.h"
#include "Renderer.h"

Node::Node()
{
	position = { 0,0 };
	scale = { 1,1 };
	pivot = { 0.5,0.5 };
	collscale = { 1,1 };

	rotation = 0;

	visible = true;
	isUI = false;

	layer = 0;

	color = Color(1,1,1,1); 
	Renderer::GetIns()->AddObject(this);
}

D3DXMATRIX Node::GetMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixTransformation2D(&m, nullptr, 0, &scale, nullptr, rotation, &position);

	if (parent != nullptr)
		return m * parent->GetMatrix();
	else return m;
}
