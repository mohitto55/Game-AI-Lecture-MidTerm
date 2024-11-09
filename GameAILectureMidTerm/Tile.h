#pragma once
#include "GameObject.h"
class Tile : public GameObject
{
public:
	int gCost;
	int hCost;
	Tile* parent;

	Tile(){}
	Tile(int x, int y, wchar_t* img, GameObjectType type) : GameObject(x, y, img, type) {}
	virtual void SetType(GameObjectType type) override;
	~Tile(){}

	int fCost() { return gCost + hCost; }
};

