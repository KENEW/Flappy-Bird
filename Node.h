#pragma once
class Node
{
public:
	Node();
	virtual ~Node() {};

	vec2 position;
	vec2 scale;
	vec2 pivot;
	vec2 collscale;

	float rotation;
	
	bool visible;
	bool isUI;
	int layer;
	
	Color color;
	RECT imgRect;

	Node* parent = nullptr;

	string tag;

	virtual void Update() {};
	virtual void Render() {};
	D3DXMATRIX GetMatrix();
	void SetParent(Node* _parent) { parent = _parent; };
};

