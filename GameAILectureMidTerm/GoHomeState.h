#pragma once
#include "BaseState.h"

class GoHomeState : public BaseState<GoHomeState>
{
protected:
	float duration = 0;
public:
	float entitySpeed;
	float stayHomeDuration;
	EColor entityColor;
	GoHomeState(float stayHomeDuration) : entitySpeed(1), stayHomeDuration(stayHomeDuration), entityColor(EColor::WHITE){};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity, float delta) override;
	virtual void ExitState(GameBaseEntity* entity) override;
	virtual string GetStateName() override { return "GoHome"; }
};

