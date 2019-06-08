#pragma once
#include "BaseEnemy.h"

#define BOSSENE_TIMETODIE 3.f
#define BOSSENE_VELOCITY Vector2(-150, 275)
#define BOSSENE_NUM_OF_BULLET 3
#define BOSSENE_WAITTIME 2.f
#define BOSSENE_SCORE 2000
#define BOSSENE_TIMETO_BEATTACKED 0.75f

class BossEnemy : public BaseEnemy
{
	/// Attributes
private:
	int numOfBullet;
	float waitTime;
	float timeToBeAtk;
	int health;
	/// Methods
private:
	Vector2 handleCollisionWithGround(float dtTime);
	void updateMoveState(float dtTime);
	void updateAttkState(float dtTime);
public:
	BossEnemy(Vector2 leftbot_wP, Vector2 size);
	virtual void onCollision();
	void render(Vector2 camera);
};