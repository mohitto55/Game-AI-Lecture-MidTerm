#pragma once
#include "CEnterMineAndForNugget.h"
#include "QuenchThirst.h"
#include "VisitBankAndDepositGold.h"
void CEnterMineAndForNugget::EnterState(GameBaseEntity* entity)
{
	BaseState<CEnterMineAndForNugget>::EnterState(entity);
	cout << "CEnterMineAndForNugget Enter" << endl;
}

void CEnterMineAndForNugget::UpdateState(GameBaseEntity* entity)
{
	BaseState<CEnterMineAndForNugget>::UpdateState(entity);

	cout << "CEnterMineAndForNugget Update" << endl;
	CMiner* Miner = dynamic_cast<CMiner*>(entity);
	if (Miner) {
		Miner->SetThirst(Miner->GetThirst() + 1);
		Miner->SetGoldCarried(Miner->GetGoldCarried() + 1);
		cout << "Thirst : " << Miner->GetThirst() << " / GoldCarried : " << Miner->GetGoldCarried() << endl;
		if (Miner->GetThirst() >= 5) {
			entity->ChangeState(QuenchThirst::GetInstance());
			return;
		}
		if (Miner->GetGoldCarried() >= 5) {
			entity->ChangeState(VisitBankAndDepositGold::GetInstance());
			return;
		}
	}
}

void CEnterMineAndForNugget::ExitState(GameBaseEntity* entity)
{
	BaseState<CEnterMineAndForNugget>::ExitState(entity);

	cout << "CEnterMineAndForNugget Exit" << endl;
}
