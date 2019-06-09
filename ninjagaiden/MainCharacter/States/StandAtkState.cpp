
#include "ninjagaidenHelper.h"
#include "StandAtkState.h"
#include "Item.h"
#include "BaseWeapon.h"
#include "BaseEnemy.h"
#include "GameWorld.h"

void StandAtkState::update(float dtTime)
{
	handleCollisionWithWater(dtTime);
	handleCollisionWithGate(dtTime);

	Vector2 displayment;
	displayment.y = handleCollisionWithGround(dtTime).y;
	displayment.x = handleCollisionWithWall(dtTime).x;
	displayment.x = displayment.y == 0 ? 0 : displayment.x;
	MainCharacter::getInstance()->position += displayment;

	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}

void StandAtkState::handleCollisionWithEnemies(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;
	MainCharacter* mainChar = MainCharacter::getInstance();
	for (unsigned int i = 2; i <= 9; i++)
	{
		tempCoEvents = mainChar->getColliWithObjsByKind((ObjKind)i, dtTime);
		coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());
	}

	for (auto coEvent : coEvents)
		if (MainCharacter::getInstance()->direction == 1 &&
			MainCharacter::getInstance()->position.x < coEvent.gameObj->position.x)
			((BaseEnemy *)coEvent.gameObj)->onCollision();
		else if (MainCharacter::getInstance()->direction == -1 &&
			MainCharacter::getInstance()->position.x > coEvent.gameObj->position.x)
			((BaseEnemy *)coEvent.gameObj)->onCollision();
		else
		{
			setState(MainCharacterState::Immortal);
			return;
		}
}

void StandAtkState::handleCollisionWithWeapons(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;
	MainCharacter* mainChar = MainCharacter::getInstance();
	for (unsigned int i = 15; i <= 17; i++)
	{
		tempCoEvents = mainChar->getColliWithObjsByKind((ObjKind)i, dtTime);
		coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());
	}

	for (auto coEvent : coEvents)
		if (MainCharacter::getInstance()->direction == 1 &&
			MainCharacter::getInstance()->position.x < coEvent.gameObj->position.x)
			((BaseWeapon*)(coEvent.gameObj))->onCollision(true);
		else if (MainCharacter::getInstance()->direction == -1 &&
			MainCharacter::getInstance()->position.x > coEvent.gameObj->position.x)
			((BaseWeapon*)(coEvent.gameObj))->onCollision(true);
		else
		{
			((BaseWeapon*)(coEvent.gameObj))->onCollision();
			setState(MainCharacterState::Immortal);
			return;
		}
}

void StandAtkState::handleCollisionWithItems(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;

	tempCoEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Item1, dtTime);
	coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());
	tempCoEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Item2, dtTime);
	coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());

	for (auto coEvent : coEvents)
		if (MainCharacter::getInstance()->direction == 1 &&
			MainCharacter::getInstance()->position.x < coEvent.gameObj->position.x)
			((Item *)(coEvent.gameObj))->onColliWithMainChar(true);
		else if (MainCharacter::getInstance()->direction == -1 &&
			MainCharacter::getInstance()->position.x > coEvent.gameObj->position.x)
			((Item *)(coEvent.gameObj))->onColliWithMainChar(true);
}

Vector2 StandAtkState::handleCollisionWithGround(float dtTime)
{
	MainCharacter::getInstance()->velocity.y += -FALL_SPEED * dtTime;
	Vector2 tempVelocity = MainCharacter::getInstance()->velocity;
	MainCharacter::getInstance()->velocity.x = 0;
	Vector2 displayment = dtTime * MainCharacter::getInstance()->velocity;

	COLLIEVENTS coEvents = MainCharacter::getInstance()
		->getColliWithObjsByKind(ObjKind::Ground, dtTime);

	for (auto coEvent : coEvents)
		if (coEvent.normal.y == 1)
		{
			displayment.y *= coEvent.colliTime;
			MainCharacter::getInstance()->velocity.y = 0;
		}

	MainCharacter::getInstance()->velocity.x = tempVelocity.x;
	return displayment;
}

void StandAtkState::handleKeyInput(bool keyStates[])
{
}
