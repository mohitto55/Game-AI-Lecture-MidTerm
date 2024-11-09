#pragma once
#include "GameBaseEntity.h"
#include "LinkedList.h"
#define LEFTDIR (int)2
#define UPDIR (int)1
#define RIGHTDIR (int)0
#define DOWNDIR  (int)3
#define NONEDIR  (int)4

#define LEFTIMG (wchar_t*)L"¢¸"
#define UPIMG (wchar_t*)L"¡ã"
#define RIGHTIMG (wchar_t*)L"¢º"
#define DOWNIMG (wchar_t*)L"¡å"
#define DOWNIMG (wchar_t*)L"¡å"

class Pacman : public GameBaseEntity
{

private:
	int moveDir;
public:
	Pacman(int x, int y, int moveDir,wchar_t* img, GameObjectType type) : GameBaseEntity(x,y,img, type) {
		this->moveDir = moveDir;
		speed = 1;
	}

	virtual void Update(float delta);
	virtual bool Collision(GameObject* other);
	void SettingImage();
	void EatItem();
};

