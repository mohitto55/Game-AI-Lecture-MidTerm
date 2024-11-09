#include "Pacman.h"
#include "GameManager.h"
#include "GameMap.h"
#include "HuntedState.h"
#include "GoHomeState.h"
#include <conio.h>
#include <typeinfo>
#include "AStar.h"
void Pacman::Update(float delta) {
	int moveX = 0;
	int moveY = 0;
	int nKey;
	if (_kbhit()) {
		nKey = _getch();
		if (nKey == 224) {
			nKey = _getch();
			switch (nKey)
			{
			case RIGHT:
				if (!IsWall(GetX() + 1, GetY())) {
					moveDir = RIGHTDIR;
				}
				break;
			case UP:
				if (!IsWall(GetX(), GetY() - 1)) {
					moveDir = UPDIR;
				}
				break;
			case LEFT:
				if (!IsWall(GetX() - 1, GetY())) {
					moveDir = LEFTDIR;
				}
				break;
			case DOWN:
				if (!IsWall(GetX(), GetY() + 1)) {
					moveDir = DOWNDIR;
				}
				break;
			}
		}
	}

	switch (moveDir)
	{
	case RIGHTDIR:
		moveX = 1;
		moveDst += speed;
		break;
	case UPDIR:
		moveY = -1;
		moveDst += speed;
		break;
	case LEFTDIR:
		moveX = -1;
		moveDst += speed;
		break;
	case DOWNDIR:
		moveY = 1;
		moveDst += speed;
	default:
		break;
	}
	int previousX = GetX();
	int previousY = GetY();
	vector<Tile*> path = AStar::Pathfinding(GetX(), GetY(), GetX() + moveX, GetY() + moveY);
	if (!Move(path)) {
		moveDir = NONEDIR;
	}
	SettingImage();

	if (GameManager::getInstance()->GetTile(GetX(), GetY())->GetType() == GameObjectType::EITEM) {
		GameManager::getInstance()->score += 50;
		GameManager::getInstance()->GetTile(GetX(), GetY())->SetType(GameObjectType::ESPACE);
		GameManager::getInstance()->GetTile(GetX(), GetY())->SetImg(SPACE);
		EatItem();

	}
	if (GameManager::getInstance()->GetTile(GetX(), GetY())->GetType() == GameObjectType::ECOIN) {
		GameMap* map = GameManager::getInstance()->GetMap();
		map->SetCoinCount(map->GetCoinCount() - 1);
		if (map->GetCoinCount() <= 0) {
			GameManager::getInstance()->GameClear();
		}
		GameManager::getInstance()->score += 10;
		GameManager::getInstance()->GetTile(GetX(), GetY())->SetType(GameObjectType::ESPACE);
		GameManager::getInstance()->GetTile(GetX(), GetY())->SetImg(SPACE);
	}
}

bool Pacman::Collision(GameObject* other)
{
	if (other->GetType() == GameObjectType::EWALL) {
		moveDir = NONEDIR;
	}
	if (other->GetType() == GameObjectType::EENEMY) {
		Enemy* enemy = static_cast<Enemy*>(other);

		// typeid는 RTTI를 써서 속도가 느리다
		if (enemy->GetCurState()->GetStateName() == "Hunter")
			GameManager::getInstance()->GameOver();

		if (enemy->GetCurState()->GetStateName() == "Hunted") {
			enemy->ChangeState(new GoHomeState(5));
			GameManager::getInstance()->score += 100;
		}
		return true;
	}
	return __super::Collision(other);
}

void Pacman::SettingImage()
{
	switch (moveDir)
	{
	case RIGHTDIR:
		SetImg(RIGHTIMG);
		break;
	case UPDIR:
		SetImg(UPIMG);
		break;
	case LEFTDIR:
		SetImg(LEFTIMG);
		break;
	case DOWNDIR:
		SetImg(DOWNIMG);
		break;
	}
}

void Pacman::EatItem()
{
	std::vector<GameObject*> objs = GameManager::getInstance()->GetGameObject(GameObjectType::EENEMY);
	for (GameObject* obj : objs) {
		Enemy* enemy = static_cast<Enemy*>(obj);

		if (enemy->GetCurState()->GetStateName() != "GoHome")
			enemy->ChangeState(new HuntedState(10));
	}
}
