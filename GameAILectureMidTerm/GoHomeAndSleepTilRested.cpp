#include "GoHomeAndSleepTilRested.h"
#include "CMiner.h"
#include "CEnterMineAndForNugget.h"
void GoHomeAndSleepTilRested::EnterState(GameBaseEntity* entity)
{
	BaseState<GoHomeAndSleepTilRested>::EnterState(entity);

	cout << "GoHomeAndSleepTilRested Enter" << endl;
	
}

void GoHomeAndSleepTilRested::UpdateState(GameBaseEntity* entity)
{
	BaseState<GoHomeAndSleepTilRested>::UpdateState(entity);

	cout << "GoHomeAndSleepTilRested Update" << endl;
	CMiner* Miner = dynamic_cast<CMiner*>(entity);
	if (Miner) {
		cout << "Your Fatigue is " << Miner->GetFatigue() << endl;
	}
	entity->ChangeState(CEnterMineAndForNugget::GetInstance());
}

void GoHomeAndSleepTilRested::ExitState(GameBaseEntity* entity)
{
	BaseState<GoHomeAndSleepTilRested>::ExitState(entity);

	cout << "GoHomeAndSleepTilRested Exit" << endl;
}
