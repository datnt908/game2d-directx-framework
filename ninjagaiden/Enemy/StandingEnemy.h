#pragma once
#include "BaseEnemy.h"

#define ENEMIES_TIME_TO_ATK 2.f
#define KNIFE_VELOCITY Vector2(100, 200)
#define KINFE_TIME_TO_DIE 1.25f
#define BULLET_VELOCITY Vector2(150, 0)
#define BULLECT_TIME_TO_DIE 1.25f

class StandingEnemy : public BaseEnemy
{
/// Attributes
protected:
	float timeToAtk;
/// Methods
private:

public:
	StandingEnemy(ObjKind kind, Vector2 position);
	virtual void updateMoveState(float dtTime);
	virtual void updateAttkState(float dtTime);
};