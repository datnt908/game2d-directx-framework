#pragma once
#include "BaseEnemy.h"

#define ENEMY2_VELOCITY Vector2(125, 0)

#define ENEMY4_VELOCITY Vector2(80, 0)
#define ENEMY4_DISTANCE_ATK 20
#define ENEMY4_TIME_TO_END_ATK 3.f

#define ENEMY5_DISTANCE_ATK 60
#define ENEMY5_VELOCITY Vector2(100, 0)

#define ENEMY7_HORIZO_SPEED 100
#define ENEMY7_FLYUP_SPEED 200
#define ENEMY7_FLYDOWN_SPEED 100

class MovingEnemy : public BaseEnemy
{
/// Attributes
protected:
	RECT moveArea;
	float timer;
/// Methods
private:
	Vector2 handleCollisionWithGround(float dtTime);
	void handleCollisionWithWater(float dtTime);
	void updateMoveStateForEnemy2(float dtTime);
	void updateMoveStateForEnemy4(float dtTime);
	void updateMoveStateForEnemy5(float dtTime);
	void updateMoveStateForEnemy7(float dtTime);
	void updateAttkStateForEnemy4(float dtTime);
public:
	MovingEnemy(ObjKind kind, Vector2 leftbot, Vector2 moveSize);
	void updateMoveState(float dtTime);
	void updateAttkState(float dtTime);
};