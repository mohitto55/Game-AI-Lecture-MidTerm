#include "LinkedList.h"
#include "GameMap.h"
#include "util.h"
#include "Pacman.h"
#include <time.h>
#include <random>
#include "GameManager.h"

int GameMap::mapWidth = 19;
int GameMap::mapHeight = 19;



int main() {
	
	
	Pacman* pacman = new Pacman(GameMap::mapWidth / 2, GameMap::mapHeight / 2, 0, PACMAN, GameObjectType::EPACMAN);
	pacman->SetImgColor(EColor::SKY);
	int map[19][19] =
	{ 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,4,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,4,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
	{1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,0,0,3,0,0,0,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1},
	{1,0,0,0,0,0,0,1,3,3,3,1,0,0,0,0,0,0,1},
	{1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
	{1,4,0,1,0,0,0,0,0,2,0,0,0,0,0,1,0,4,1},
	{1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} 
	};

	// int[19][19]을 int**로 변환
	int** dynamicMap = new int* [19];
	for (int i = 0; i < 19; ++i) {
		dynamicMap[i] = map[i];
	}
	std::vector<GameObject*> objs;
	GameMap* gameMap = new GameMap(dynamicMap, GameMap::mapWidth, GameMap::mapHeight, objs);
	clock_t oldTime, curTime;
	float delta = 0;
	oldTime = clock();
	curTime = clock();
	int FPS = 15;

	srand(time(NULL));
	GameManager::getInstance()->initGame(objs, gameMap);
	ScreenInit();
	while (1) {
		GameManager::getInstance()->Update(delta);
		ScreenClear(GameMap::mapWidth, GameMap::mapHeight);
		GameManager::getInstance()->draw(delta);
		ScreenFlipping();
		while (1) {
			curTime = clock();
			if (curTime - oldTime >= 1000.f / FPS) {
				delta = (curTime - oldTime) / 1000.f;
				oldTime = curTime;
				break;
			}
		}
	}
	ScreenRelease();
	return 0;
}