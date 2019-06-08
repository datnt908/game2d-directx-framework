#pragma once
#include "InteractiveObj.h"
#include "ninjagaidenHelper.h"

#define ENEMIES_DYING_ANIS_ID 10
#define ENEMIES_TIMETODIE 0.25f

enum EnemyState
{
	MOVE = 0,
	ATTACK = 1,
	DEAD = 2
};

class BaseEnemy : public InteractiveObj
{
/// Attributes
protected:
	static unordered_map<int, LPANIS> anicollectS;
	EnemyState state = EnemyState::MOVE;
	int direction;
	float timeToDie;
	float deltamovex1;
	float deltamovex2;

/// Methods
protected:

	virtual void updateMoveState(float dtTime);
	virtual void updateAttkState(float dtTime);
	virtual void updateDeadState(float dtTime);
public:
	static bool loadResource();
	static void releaseResource();

	virtual void update(float dtTime);
	virtual void render(Vector2 cam_wP);
	virtual void onCollision();
};