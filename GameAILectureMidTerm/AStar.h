#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <vector>

using namespace std;
class AStar
{
public:
	static vector<Tile*> Pathfinding(int startX, int startY, int endX, int endY, bool findNeighbour = false);
	static int GetDistance(int x1, int y1, int x2, int y2);
	static int GetDistance(GameObject* v1, GameObject* v2);
	static vector<Tile*> RetracePath(Tile* startTile, Tile* endTile);
};

