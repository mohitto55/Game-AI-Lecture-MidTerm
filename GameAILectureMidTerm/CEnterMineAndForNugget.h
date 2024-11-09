#pragma once
#include "BaseState.h"
#include "CMiner.h"
class CEnterMineAndForNugget : public BaseState<CEnterMineAndForNugget>
{
public:
	CEnterMineAndForNugget() {};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity) override;
	virtual void ExitState(GameBaseEntity* entity) override;
};