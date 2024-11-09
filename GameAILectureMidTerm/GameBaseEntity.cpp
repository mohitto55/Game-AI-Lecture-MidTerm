#include "GameBaseEntity.h"

bool GameBaseEntity::Move(std::vector<Tile*> path)
{
	if (path.size() == 0)
		return false;
	int pathIndex = 0;
	while (moveDst >= 1 && pathIndex < path.size()) {
		SetX(path[pathIndex]->GetX());
		SetY(path[pathIndex]->GetY());

		moveDst -= 1;
		pathIndex += 1;
	}
	return true;
}
