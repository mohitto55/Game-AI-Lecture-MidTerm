#include "CMiner.h"


CMiner::CMiner(string name, CState* startState) : GameBaseEntity(name)
{
	m_pCurState = startState;
	m_iGoldCarried = 0;
	m_iMoneyInBank = 0;
	m_iThirst = 0;
	m_iFatigue = 0;
}

void CMiner::Update()
{
	m_pCurState->UpdateState(this);
}

void CMiner::ChangeState(CState* newState)
{
	m_pCurState->ExitState(this);
	m_pCurState = newState;
	m_pCurState->EnterState(this);
}
