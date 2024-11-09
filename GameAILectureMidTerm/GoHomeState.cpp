#include "GoHomeState.h"
#include "GameBaseEntity.h"
#include "AStar.h"
#include "Enemy.h"
#include "HunterState.h"
void GoHomeState::EnterState(GameBaseEntity* entity)
{
	entitySpeed = entity->GetSpeed();
	entityColor = entity->GetColor();
	entity->SetSpeed(entitySpeed * 2);
	entity->SetImgColor(EColor::GREEN);
}

void GoHomeState::UpdateState(GameBaseEntity* entity, float delta)
{
	Enemy* enemy = static_cast<Enemy*>(entity);
	std::vector<Tile*> path = AStar::Pathfinding(entity->GetX(), entity->GetY(), enemy->GetSpawnX(), enemy->GetSpawnY());
	if (!entity->Move(path)) {
		if (stayHomeDuration <= 0) {
			entity->ChangeState(new HunterState());
		}
		stayHomeDuration -= delta;
	}
}

void GoHomeState::ExitState(GameBaseEntity* entity)
{
	stayHomeDuration = 0;
	entity->SetSpeed(entitySpeed);
	entity->SetImgColor(entityColor);
}
