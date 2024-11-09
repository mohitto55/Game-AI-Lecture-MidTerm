#pragma once
#include "GameBaseEntity.h"


class CMiner : public GameBaseEntity {
	CState* m_pCurState;
	int m_iGoldCarried;
	int m_iMoneyInBank;
	int m_iThirst;
	int m_iFatigue;
public:
	CMiner(string name, CState* startState);
	int GetGoldCarried() { return m_iGoldCarried; }
	int GetMoneyInBank() { return m_iMoneyInBank; }
	int GetThirst() { return m_iThirst; }
	int GetFatigue() { return m_iFatigue; }
	void SetGoldCarried(int value) { m_iGoldCarried = value; }
	void SetMoneyInBank(int value) { m_iMoneyInBank = value; }
	void SetThirst(int value) { m_iThirst = value; }
	void SetFatigue(int value) { m_iFatigue = value; }

	const CState* GetCurState() { return m_pCurState; } 
	virtual ~CMiner() {}
	virtual void Update() override;
	virtual void ChangeState(CState* newState) override;
};