#pragma once
#include "BaseState.h"

class GoHomeAndSleepTilRested : public BaseState<GoHomeAndSleepTilRested>
{
public:
	GoHomeAndSleepTilRested() {};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity) override;
	virtual void ExitState(GameBaseEntity* entity) override;
};