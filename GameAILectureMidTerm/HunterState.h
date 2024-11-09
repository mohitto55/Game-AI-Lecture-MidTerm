#pragma once
#include "BaseState.h"

class Enemy;
class HunterState : public BaseState<HunterState>
{
public:
	HunterState() {};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity, float delta) override;
	virtual void ExitState(GameBaseEntity* entity) override;
	void ResetPatrolPosition(Enemy* enemy);
	void Patrol(Enemy* enemy);
	virtual string GetStateName() override { return "Hunter"; }
};