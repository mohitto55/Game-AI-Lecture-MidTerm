#pragma once
#include <iostream>
#include "string.h"
#include "GameObject.h"

using namespace std;
class GameBaseEntity;
class CState;

class CState {
public:
	virtual void EnterState(GameBaseEntity* entity) = 0;
	virtual void UpdateState(GameBaseEntity* entity) = 0;
	virtual void ExitState(GameBaseEntity* entity) = 0;
};

class GameBaseEntity : public GameObject
{
private:
	string m_name;
public:
	GameBaseEntity(string name) : m_name(name){}
	virtual void Update() = 0;
	virtual void ChangeState(CState* newState) = 0;
	string getName() { return m_name; }
};

class Enemy : public GameObject
{
private:
	int moveDir = 0;
	int respawnX = 0;
	int respawnY = 0;
public:
	Enemy(int x, int y, wchar_t* img, GameObjectType type) : GameObject(x, y, img, type) {
		respawnX = x;
	}
};
