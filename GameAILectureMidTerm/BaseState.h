#pragma once
#include "GameBaseEntity.h"

template <class T>
class BaseState : public CState {
public:
	BaseState(){}
	virtual void EnterState(GameBaseEntity* entity) override {}
	virtual void UpdateState(GameBaseEntity* entity, float delta) override {}
	virtual void ExitState(GameBaseEntity* entity) override {}
	virtual string GetStateName() override { return ""; };
};