#include "HuntedState.h"
#include "HunterState.h"
#include "GameManager.h"
#include <math.h>
#include "AStar.h"
void HuntedState::EnterState(GameBaseEntity* entity)
{
	BaseState<HuntedState>::EnterState(entity);
	entityColor = entity->GetColor();
	entity->SetImgColor(EColor::BLUE);
}

void HuntedState::UpdateState(GameBaseEntity* entity, float delta)
{
	BaseState<HuntedState>::UpdateState(entity, delta);
	std::vector<GameObject*> pacmans = GameManager::getInstance()->GetGameObject(GameObjectType::EPACMAN);
	if (pacmans.size() > 0) {
		GameObject* pacman = pacmans[0];
		int nx = entity->GetX() < pacman->GetX() ? -1 : 1;
		int ny = entity->GetY() < pacman->GetY() ? -1 : 1;

		std::vector<Tile*> path = AStar::Pathfinding(entity->GetX(), entity->GetY(), entity->GetX() + nx, entity->GetY() + ny, true);
		entity->Move(path);
	}
	
	if (duration <= 0) {
		entity->ChangeState(new HunterState());
	}
	duration -= delta;
}

void HuntedState::ExitState(GameBaseEntity* entity)
{
	BaseState<HuntedState>::ExitState(entity);
	entity->SetImgColor(entityColor);
}
