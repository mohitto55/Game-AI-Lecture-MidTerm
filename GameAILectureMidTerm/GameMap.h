#pragma once
#include "GameObject.h"
#include <iostream>
#include <vector>
#include "Tile.h"

class GameMap
{
	int width;
	int height;
	Tile** map;
	int coinCount = 0;
public:
	static int mapWidth;
	static int mapHeight;

	GameMap(int w, int h);
	GameMap(int** _map, int w, int h, std::vector<GameObject*>& generatedObjects);
	~GameMap();
	void initMap();
	Tile* getTile(int x, int y);
	Tile* GetRandomTile() {
		int randX = rand() % this->width;
		int randY = rand() % this->height;
		if (InMap(randX, randY)) {
			return &map[randY][randX];
		}
		return nullptr;
	}
	void setTile(int x, int y, Tile obj);
	bool InMap(int x,int y);
	std::vector<Tile*> GetNeighbourTiles(int x,int y);

	const int getWidth() { return width; }
	const int getHeight() { return height; }
	const void SetCoinCount(int count) { coinCount = count; }
	const int GetCoinCount() { return coinCount; }

	void draw();
};
