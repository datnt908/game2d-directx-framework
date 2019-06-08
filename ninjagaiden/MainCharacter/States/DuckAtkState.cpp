#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "DuckState.h"
#include "DuckAtkState.h"
#include "MainCharacter.h"
#include "BaseWeapon.h"
#include "BaseEnemy.h"
#include "GameWorld.h"

void DuckAtkState::update(float dtTime)
{
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}

void DuckAtkState::handleCollisionWithEnemies(float dtTime)
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
			MainCharacter::getInstance()->position.x < coEvent->gameObj->position.x)
			((BaseEnemy *)coEvent->gameObj)->onCollision();
		else if (MainCharacter::getInstance()->direction == -1 &&
			MainCharacter::getInstance()->position.x > coEvent->gameObj->position.x)
			((BaseEnemy *)coEvent->gameObj)->onCollision();
		else
		{
			setState(MainCharacterState::Immortal);
			return;
		}

}

void DuckAtkState::handleCollisionWithWeapons(float dtTime)
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
			MainCharacter::getInstance()->position.x < coEvent->gameObj->position.x)
			((BaseWeapon*)(coEvent->gameObj))->onCollision(true);
		else if (MainCharacter::getInstance()->direction == -1 &&
			MainCharacter::getInstance()->position.x > coEvent->gameObj->position.x)
			((BaseWeapon*)(coEvent->gameObj))->onCollision(true);
		else
		{
			((BaseWeapon*)(coEvent->gameObj))->onCollision();
			setState(MainCharacterState::Immortal);
			return;
		}
}

void DuckAtkState::handleKeyInput(bool keyStates[])
{
}
