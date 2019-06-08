#include "MovingEnemy.h"

MovingEnemy::MovingEnemy(ObjKind kind, Vector2 leftbot, Vector2 moveSize):
	BaseEnemy(kind, leftbot)
{
	position.x = rand() % ((int)moveSize.x) + leftbot.x;
	position.y = leftbot.y;
	direction = -1;
}

void MovingEnemy::updateMoveState(float dtTime)
{
}

void MovingEnemy::updateAttkState(float dtTime)
{
}
