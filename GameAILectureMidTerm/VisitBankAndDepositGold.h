#pragma once
#include "BaseState.h"

class VisitBankAndDepositGold : public BaseState<VisitBankAndDepositGold>
{
public:
	VisitBankAndDepositGold() {};
	virtual void EnterState(GameBaseEntity* entity) override;
	virtual void UpdateState(GameBaseEntity* entity) override;
	virtual void ExitState(GameBaseEntity* entity) override;
};