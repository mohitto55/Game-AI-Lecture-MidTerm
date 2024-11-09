#pragma once
#include "util.h"


#define WALL (wchar_t*)L"¡á"
#define SPACE (wchar_t*)L" "
#define PACMAN (wchar_t*)L"¢Á"
#define ENEMY (wchar_t*)L"¡ß"
#define COIN (wchar_t*)L"¡Û"
#define ITEM (wchar_t*)L"¡Ú"

enum class GameObjectType : int {
	ESPACE = 0,
	EWALL = 1,
	EPACMAN = 2,
	EENEMY = 3,
	EITEM = 4,
	ECOIN = 5,
};

enum class EColor : int {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	SKY = 3,
	RED = 4,
	PURPLE = 5,
	YELLOW = 6,
	WHITE = 7,
};

class GameObject
{
protected:
	int x;
	int y;
	EColor color = EColor::WHITE;
	wchar_t* img;
	GameObjectType type;
public:
	GameObject() : x(0), y(0), img((wchar_t*)L" "), type(GameObjectType::ESPACE) {}
	GameObject(int x, int y, wchar_t* img, GameObjectType type) : x(x), y(y), img(img), type(type) {}
	virtual ~GameObject() {}
	const int GetX() { return x; }
	const int GetY() { return y; }
	wchar_t* GetImg() { return img; }

	bool IsWall(int x,int y);
	bool SetX(int x);
	bool SetY(int y);
	void SetImg(wchar_t* img) { this->img = img; }
	EColor GetColor() { return color; }
	bool IsSamePosition(GameObject* other) {
		if (x == other->x && y == other->y)
			return true;
		return false;
	}

	virtual void SetType(GameObjectType type) { this->type = type; }
	void SetImgColor(EColor color) { this->color = color; }
	const GameObjectType GetType() { return type; }

	virtual	void Update(float delta) { }

	virtual bool Collision(GameObject* other) {
		if (other->GetX() == this->x && other->GetY() == this->y) {
			return true;
		}
		return false;
	}
	virtual void draw() {
		SetColor(static_cast<int>(color));
		ScreenPrint(x, y, img);
	}
};
