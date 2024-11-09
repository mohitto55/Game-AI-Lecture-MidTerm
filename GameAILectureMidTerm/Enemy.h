#pragma once
#include "GameObject.h"
#include "GameBaseEntity.h"
#include "LinkedList.h"
#include "BaseState.h"
#include "HunterState.h"
#include "Tile.h"
#include <vector>
#define LEFTDIR (int)2
#define UPDIR (int)1
#define RIGHTDIR (int)0
#define DOWNDIR  (int)3



class Enemy : public GameBaseEntity
{
private:
	CState* curState;
	int moveDir = 0;
	int respawnX = 0;
	int respawnY = 0;
	int chaseDst = 0;
	int patrolX = -1;
	int patrolY = -1;
public:
	Enemy(int x, int y, wchar_t* img, GameObjectType type) : GameBaseEntity(x, y, img, type) {
		curState = new HunterState();
		respawnX = x;
		respawnY = y;
		chaseDst = 50;
	}
	virtual ~Enemy();
	virtual	void Update(float delta) override;
	virtual void ChangeState(CState* newState) override;
	int GetChaseDst() { return chaseDst; }
	int GetPatrolX() { return patrolX; }
	int GetPatrolY() { return patrolY; }
	int GetSpawnX() { return respawnX; }
	int GetSpawnY() { return respawnY; }
	CState* GetCurState() { return curState; }
	void SetPatrolX(const int x) { patrolX = x; }
	void SetPatrolY(const int y) { patrolY = y; }
	int Clamp(int x, int min, int max);
};

