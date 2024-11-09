#pragma once
#include "BaseState.h"

class QuenchThirst : public BaseState<QuenchThirst>
{
public:
	QuenchThirst() {};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity) override;
	virtual void ExitState(GameBaseEntity* entity) override;
};