#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "DuckState.h"
#include "DuckAtkState.h"
#include "MainCharacter.h"
#include "BaseWeapon.h"
#include "BossEnemy.h"
#include "GameWorld.h"

void DuckAtkState::update(float dtTime)
{
	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}

void DuckAtkState::handleCollisionWithEnemies(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;
	MainCharacter* mainChar = MainCharacter::getInstance();
	for (unsigned int i = 2; i <= 8; i++)
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
			setState(MainCharacterState::Immortal);
			return;
		}
}

void DuckAtkState::handleCollisionWithBoss(float dtTime)
{
	COLLIEVENTS coEvents;
	coEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Boss, dtTime);

	for (auto coEvent : coEvents)
		if (MainCharacter::getInstance()->direction == 1 &&
			MainCharacter::getInstance()->position.x < coEvent->gameObj->position.x)
			((BossEnemy *)coEvent->gameObj)->onCollision();
		else if (MainCharacter::getInstance()->direction == -1 &&
			MainCharacter::getInstance()->position.x > coEvent->gameObj->position.x)
			((BossEnemy *)coEvent->gameObj)->onCollision();
		else
			setState(MainCharacterState::Immortal);
}

void DuckAtkState::handleKeyInput(bool keyStates[])
{
}
