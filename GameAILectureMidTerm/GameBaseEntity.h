#pragma once
#include <iostream>
#include "string.h"
#include "GameObject.h"
#include <vector>
#include "Tile.h"
using namespace std;
class GameBaseEntity;
class CState;

class CState {
public:
	virtual void EnterState(GameBaseEntity* entity) = 0;
	virtual void UpdateState(GameBaseEntity* entity, float delta) = 0;
	virtual void ExitState(GameBaseEntity* entity) = 0;
	virtual string GetStateName() = 0;
};

class GameBaseEntity : public GameObject
{
protected:
	float speed = 3.f;
	float moveDst = 0;
public:
	GameBaseEntity(int x, int y, wchar_t* img, GameObjectType type) : GameObject(x, y, img, type) {}
	virtual ~GameBaseEntity() {};
	virtual void ChangeState(CState* newState) {};
	float GetSpeed() { return speed; }
	void SetSpeed(float speed) { this->speed = speed; }
	bool Move(std::vector<Tile*> path);
};