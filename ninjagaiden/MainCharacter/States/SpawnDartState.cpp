#include "CollisionEvent.h"
#include "ninjagaidenHelper.h"
#include "SpawnDartState.h"

void SpawnDartState::update(float dtTime)
{
	handleCollisionWithWater(dtTime);
	handleCollisionWithGate(dtTime);

	Vector2 displayment;
	displayment.y = handleCollisionWithGround(dtTime).y;
	displayment.x = handleCollisionWithWall(dtTime).x;
	displayment.x = displayment.y == 0 ? 0 : displayment.x;
	MainCharacter::getInstance()->position += displayment;

	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}

void SpawnDartState::handleKeyInput(bool keyStates[])
{
}

Vector2 SpawnDartState::handleCollisionWithGround(float dtTime)
{
	MainCharacter::getInstance()->velocity.y += -FALL_SPEED * dtTime;
	Vector2 tempVelocity = MainCharacter::getInstance()->velocity;
	MainCharacter::getInstance()->velocity.x = 0;
	Vector2 displayment = dtTime * MainCharacter::getInstance()->velocity;

	COLLIEVENTS coEvents = MainCharacter::getInstance()
		->getColliWithObjsByKind(ObjKind::Ground, dtTime);

	for (auto coEvent : coEvents)
		if (coEvent->normal.y == 1)
		{
			displayment.y *= coEvent->colliTime;
			MainCharacter::getInstance()->velocity.y = 0;
		}

	MainCharacter::getInstance()->velocity.x = tempVelocity.x;
	return displayment;
}
