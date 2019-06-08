#include <dinput.h>
#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "ClimbState.h"
#include "JumpState.h"
#include "MainCharacter.h"
#include "GameWorld.h"

void ClimbState::update(float dtTime)
{
	handleCollisionWithStair(dtTime);

	Vector2 displayment = dtTime * MainCharacter::getInstance()->velocity;
	displayment.x = 0;
	MainCharacter::getInstance()->position += displayment;

	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}

void ClimbState::handleCollisionWithStair(float dtTime)
{
	COLLIEVENTS coEvents;
	MainCharacter::getInstance()->velocity.x = 1;
	coEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Stair, dtTime);

	if (!coEvents.size())
	{
		coEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Stair, dtTime);
		setState(MainCharacterState::Jump);
		MainCharacter::getInstance()->velocity.y = MAINCHAR_JUMP_SPEED;
	}
	MainCharacter::getInstance()->velocity.x = 0;
}

void ClimbState::handleKeyInput(bool keyStates[])
{
	if (keyStates[DIK_UP] && !keyStates[DIK_DOWN])
	{
		MainCharacter::getInstance()->velocity.y = MAINCHAR_MOVE_SPEED;
	}
	else if (keyStates[DIK_DOWN] && !keyStates[DIK_UP])
	{
		MainCharacter::getInstance()->velocity.y = -MAINCHAR_MOVE_SPEED;
	}
	else
		MainCharacter::getInstance()->velocity.y = 0;

	if (keyStates[DIK_LEFT])
	{
		MainCharacter::getInstance()->setDirection(-1);
		MainCharacter::getInstance()->velocity.x = -MAINCHAR_MOVE_SPEED;
		MainCharacter::getInstance()->velocity.y = MAINCHAR_JUMP_SPEED;
		setState(MainCharacterState::Jump);
	}
	
}
