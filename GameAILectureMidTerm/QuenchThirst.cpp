#include "QuenchThirst.h"
#include "CMiner.h"
#include "CEnterMineAndForNugget.h"
void QuenchThirst::EnterState(GameBaseEntity* entity)
{
	BaseState<QuenchThirst>::EnterState(entity);

	cout << "QuenchThirst Enter" << endl;
}

void QuenchThirst::UpdateState(GameBaseEntity* entity)
{
	BaseState<QuenchThirst>::UpdateState(entity);

	cout << "QuenchThirst Update" << endl;
	CMiner* Miner = dynamic_cast<CMiner*>(entity);
	if (Miner) {
		Miner->SetThirst(0);
		cout << "Your Thirst is " << Miner->GetThirst() << endl;
	}
	entity->ChangeState(CEnterMineAndForNugget::GetInstance());
}

void QuenchThirst::ExitState(GameBaseEntity* entity)
{
	BaseState<QuenchThirst>::ExitState(entity);

	cout << "QuenchThirst Exit" << endl;
}
