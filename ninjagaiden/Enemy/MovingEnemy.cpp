#include "MovingEnemy.h"
#include "MainCharacter.h"

#include "GameWorld.h"

Vector2 MovingEnemy::handleCollisionWithGround(float dtTime)
{
	velocity.y += -FALL_SPEED * dtTime;
	Vector2 displayment = dtTime * velocity;

	COLLIEVENTS coEvents;
	calculateColli(
		GameWorld::getInstance()->getInProcObjs(ObjKind::Ground),
		dtTime, coEvents
	);

	for (auto coEvent : coEvents)
		if (coEvent.normal.y == 1)
		{
			displayment.y *= coEvent.colliTime;
			velocity.y = 0;
		}

	return displayment;
}

void MovingEnemy::handleCollisionWithWater(float dtTime)
{
	COLLIEVENTS coEvents;
	calculateColli(
		GameWorld::getInstance()->getInProcObjs(ObjKind::Water),
		dtTime, coEvents
	);
	if (coEvents.size())
		if (coEvents[0].normal = Vector2(0, 0))
			GameWorld::getInstance()->deleteObject(this);
}

void MovingEnemy::updateMoveStateForEnemy2(float dtTime)
{
	position.x += direction * dtTime * ENEMY2_VELOCITY.x;
	position.y += handleCollisionWithGround(dtTime).y;
	handleCollisionWithWater(dtTime);
}

void MovingEnemy::updateMoveStateForEnemy4(float dtTime)
{
	position.x += direction * dtTime * ENEMY4_VELOCITY.x;
	Vector2 mainPos = MainCharacter::getInstance()->position;

	if ((mainPos.x - position.x) * direction >= 0)
		if (abs(mainPos.x - position.x) <= ENEMY4_DISTANCE_ATK)
		{
			state = EnemyState::ATTACK;
			timer = ENEMY4_TIME_TO_END_ATK;
		}

	if (position.x < moveArea.left) direction = 1;
	if (position.x > moveArea.right) direction = -1;
}

void MovingEnemy::updateMoveStateForEnemy5(float dtTime)
{
	Vector2 mainPos = MainCharacter::getInstance()->position;
	if (mainPos.x < moveArea.left || mainPos.x > moveArea.right)
	{
		if (position.x < moveArea.left) direction = 1;
		if (position.x > moveArea.right) direction = -1;
	}
	else if ((mainPos.x - position.x) * direction <= 0)
		if (abs(mainPos.x - position.x) >= ENEMY5_DISTANCE_ATK)
		{
			if (position.x < mainPos.x) direction = 1;
			else direction = -1;
		}
	
	position.x += direction * dtTime * ENEMY2_VELOCITY.x;
	
}

void MovingEnemy::updateMoveStateForEnemy7(float dtTime)
{
	Vector2 mainPos = MainCharacter::getInstance()->position;
	if (mainPos.x < moveArea.left || mainPos.x > moveArea.right)
	{
		if (position.y < moveArea.top)
			velocity.y = ENEMY7_FLYUP_SPEED;
		else
			velocity.y = 0;
		if (position.x < moveArea.left) direction = 1;
		if (position.x > moveArea.right) direction = -1;
	}
	else
	{
		if ((mainPos.x - position.x) * direction <= 0)
			if (abs(mainPos.x - position.x) >= ENEMY5_DISTANCE_ATK)
			{
				if (position.x < mainPos.x) direction = 1;
				else direction = -1;
			}
		if ((mainPos.y - position.y) <= 0)
		{
			if (mainPos.y - position.y <= -ENEMY5_DISTANCE_ATK)
				velocity.y = -ENEMY7_FLYDOWN_SPEED;
		}
		else
			velocity.y = ENEMY7_FLYUP_SPEED;

	}
	velocity.x = ENEMY7_HORIZO_SPEED * direction;
	position += velocity * dtTime;
}

void MovingEnemy::updateAttkStateForEnemy4(float dtTime)
{
	timer -= dtTime;
	if (timer <= 0)
		state = EnemyState::MOVE;
}

MovingEnemy::MovingEnemy(ObjKind kind, Vector2 leftbot, Vector2 moveSize):
	BaseEnemy(kind, leftbot)
{
	position.x = rand() % ((int)moveSize.x) + leftbot.x;
	position.y = leftbot.y;
	if (kind == ObjKind::Enemy7)
		position.y = leftbot.y + moveSize.y;
	direction = -1;
	moveArea.bottom = leftbot.y;
	moveArea.left = leftbot.x;
	moveArea.top = leftbot.y + moveSize.y;
	moveArea.right = leftbot.x + moveSize.x;
}

void MovingEnemy::updateMoveState(float dtTime)
{
	switch (enemyKind)
	{
	case Enemy2:
		updateMoveStateForEnemy2(dtTime);
		break;
	case Enemy4:
		updateMoveStateForEnemy4(dtTime);
		break;
	case Enemy5:
		updateMoveStateForEnemy5(dtTime);
		break;
	case Enemy7:
		updateMoveStateForEnemy7(dtTime);
		break;
	default:
		break;
	}
}

void MovingEnemy::updateAttkState(float dtTime)
{
	if (enemyKind == ObjKind::Enemy4)
		updateAttkStateForEnemy4(dtTime);
}
