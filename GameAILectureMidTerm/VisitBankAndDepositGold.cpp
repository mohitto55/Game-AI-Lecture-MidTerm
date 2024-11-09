#include "VisitBankAndDepositGold.h"
#include "CMiner.h"
#include "GoHomeAndSleepTilRested.h"
void VisitBankAndDepositGold::EnterState(GameBaseEntity* entity)
{
	BaseState<VisitBankAndDepositGold>::EnterState(entity);
	cout << "VisitBankAndDepositGold Enter" << endl;
	CMiner* Miner = dynamic_cast<CMiner*>(entity);
	if (Miner) {
		// 은행에 돈 저장
		int goldCarried = Miner->GetGoldCarried();
		cout << "You " << goldCarried << " GoldCarried" << endl;
		Miner->SetMoneyInBank(Miner->GetMoneyInBank() + goldCarried);
		Miner->SetGoldCarried(0);
	}
}

void VisitBankAndDepositGold::UpdateState(GameBaseEntity* entity)
{
	BaseState<VisitBankAndDepositGold>::UpdateState(entity);
	cout << "VisitBankAndDepositGold Update" << endl;
	CMiner* Miner = dynamic_cast<CMiner*>(entity);
	if (Miner) {
		int moneyInBank = Miner->GetMoneyInBank();
		if (moneyInBank >= 8) {
			cout << "You Are So Rich!" << endl;
			Miner->ChangeState(GoHomeAndSleepTilRested::GetInstance());
			return;
		}
		else {
			cout << "You Are Not Rich..." << endl;
			Miner->ChangeState(GoHomeAndSleepTilRested::GetInstance());
			return;
		}
	}
}

void VisitBankAndDepositGold::ExitState(GameBaseEntity* entity)
{
	BaseState<VisitBankAndDepositGold>::ExitState(entity);
	cout << "VisitBankAndDepositGold Exit" << endl;
}
