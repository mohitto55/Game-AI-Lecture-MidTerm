#include "Enemy.h"
#include <algorithm>
#include <math.h>
Enemy::~Enemy()
{
	if (curState) {
		delete curState;
	}
}

void Enemy::Update(float delta)
{
	curState->UpdateState(this, delta);
	moveDst += speed * delta;
	if(moveDst >= 1)
	moveDst = Clamp(moveDst, 1, speed);
}

void Enemy::ChangeState(CState* newState)
{
	if (curState) {
		curState->ExitState(this);
		delete curState;
	}
	curState = newState;
	curState->EnterState(this);
}

int Enemy::Clamp(int x, int min, int max)
{
	if (x > max) x = max;
	if (x < min) x = min;
	return x;
}
