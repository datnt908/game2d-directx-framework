#pragma once
#include "InteractiveObj.h"
#include "ninjagaidenHelper.h"

#define ENEMIES_DYING_ANIS_ID 10
#define ENEMIES_TIME_TO_DIE 0.25f

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
	EnemyState state;
	ObjKind enemyKind;
	int direction;
	float timeToDie;

/// Methods
protected:

	virtual void updateMoveState(float dtTime) = 0;
	virtual void updateAttkState(float dtTime) = 0;
	virtual void updateDeadState(float dtTime);
public:
	static bool loadResource();
	static void releaseResource();
	BaseEnemy(ObjKind kind, Vector2 position);
	virtual void update(float dtTime);
	virtual void render(Vector2 camera);
	virtual void onCollision();
	virtual BndBox getBndBox(float dtTime);
};