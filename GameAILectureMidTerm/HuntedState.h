#pragma once
#include "BaseState.h"
class HuntedState : public BaseState<HuntedState>
{
protected:
	float duration = 0;
public:
	EColor entityColor;
	HuntedState(float duration) : duration(duration), entityColor(EColor::WHITE){};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity, float delta) override;
	virtual void ExitState(GameBaseEntity* entity) override;
	virtual string GetStateName() override { return "Hunted"; }
};