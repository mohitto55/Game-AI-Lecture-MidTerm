#include "GameObject.h"
#include "GameManager.h"
#include "GameMap.h"
bool GameObject::IsWall(int x, int y)
{
	if (GameManager::getInstance()->GetTile(x, y)->GetType() == GameObjectType::EWALL) {
		return true;
	}
	return false;
}
bool GameObject::SetX(int x)
{
	if (!IsWall(x, this->y)) {
		this->x = x;
		return true;
	}
	return false;
}

bool GameObject::SetY(int y)
{
	if (!IsWall(this->x, y)) {
		this->y = y;
		return true;
	}
	return false;
}