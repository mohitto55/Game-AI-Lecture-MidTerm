#pragma once
#include "LinkedList.h"
#include "GameMap.h"
#include "Pacman.h"
#include "Enemy.h"
#include <vector>


class GameManager
{
	Pacman* pacman;
	GameMap* gameMap;
	std::vector<GameObject*> objects;
	GameManager() {}
	int textLine = 0;
	bool isGameClear = false;
	bool isGameOver = false;
	float blink = 0;
	EColor blinkColor = EColor::WHITE;
public:
	int score = 0;
	static GameManager* getInstance() {
		static GameManager* instance;
		if (instance == nullptr) {
			instance = new GameManager();
		}
		return instance;
	}

	void initGame(std::vector<GameObject*> otherObjects, GameMap* map);

	/*GameObject* GetPacman() { return pacman; }*/
	GameMap* GetMap() { return gameMap; }
	std::vector<GameObject*> GetGameObject(GameObjectType findType);
	Tile* GetTile(int x,int y) { return GetMap()->getTile(x, y); }
	void Update(float delta);
	void draw(float delta);
	void AddObject(GameObject* gameObject);
	void SetPacman(Pacman* pacman) { this->pacman = pacman; }
	void SetTextColor(EColor color);
	void PrintText(const wchar_t* t);
	void GameOver() { if(!isGameClear) this->isGameOver = true; }
	void GameClear() { if(!isGameOver) this->isGameClear = true; }
};
