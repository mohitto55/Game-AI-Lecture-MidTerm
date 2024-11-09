#include "HunterState.h"
#include "Enemy.h"
#include "AStar.h"
#include "GameManager.h"
void HunterState::EnterState(GameBaseEntity* entity)
{
	Enemy* enemy = static_cast<Enemy*>(entity);
	if (enemy != nullptr)
		ResetPatrolPosition(enemy);
}

void HunterState::UpdateState(GameBaseEntity* entity, float delta)
{
	Enemy* enemy = static_cast<Enemy*>(entity);

	if (enemy->GetPatrolX() == -1 || enemy->GetPatrolY() == -1)
		ResetPatrolPosition(enemy);

	std::vector<GameObject*> pacmans = GameManager::getInstance()->GetGameObject(GameObjectType::EPACMAN);
	if (pacmans.size() > 0) {
		GameObject* pacman = pacmans[0];

		// 거리가 가까우면 추적한다.
		if (enemy->GetChaseDst() >= AStar::GetDistance(pacman, enemy)) {
			vector<Tile*> path = AStar::Pathfinding(entity->GetX(), entity->GetY(), pacman->GetX(), pacman->GetY());
			enemy->Move(path);
		}
		// 거리가 멀면 배회한다.`
		else {
		    Patrol(enemy);
		}		
	}
	
}

void HunterState::ExitState(GameBaseEntity* entity)
{
}

void HunterState::ResetPatrolPosition(Enemy* enemy)
{
	if (GameManager::getInstance()->GetMap() == nullptr)
		return;

	Tile* tile = GameManager::getInstance()->GetMap()->GetRandomTile();

	vector<Tile*> path = AStar::Pathfinding(enemy->GetX(), enemy->GetY(), tile->GetX(), tile->GetY());
	if (path.size() == 0) {
		ResetPatrolPosition(enemy);
		return;
	}

	Tile* lastTile = path[path.size() - 1];
	if (lastTile) {
		enemy->SetPatrolX(lastTile->GetX());
		enemy->SetPatrolY(lastTile->GetY());
	}
}

void HunterState::Patrol(Enemy* enemy)
{
	vector<Tile*> path = AStar::Pathfinding(enemy->GetX(), enemy->GetY(), enemy->GetPatrolX(), enemy->GetPatrolY());
	if (path.size() > 0) {
		enemy->Move(path);
	}
	// 경로에 도달했으면 다른 경로를 탐색한다.
	else {
		ResetPatrolPosition(enemy);
		Patrol(enemy);
	}
}
