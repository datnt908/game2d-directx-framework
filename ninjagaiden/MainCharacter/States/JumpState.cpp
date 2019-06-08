#include <dinput.h>
#include "CollisionEvent.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "ninjagaidenHelper.h"
#include "JumpState.h"

void JumpState::update(float dtTime)
{
	handleCollisionWithWater(dtTime);
	handleCollisionWithGate(dtTime);

	Vector2 displayment;
	displayment.y = handleCollisionWithGround(dtTime).y;
	if (displayment.y == 0)
	{
		MainCharacter::getInstance()->velocity.y = 0;
		setState(MainCharacterState::Idle);
	}
	displayment.x = handleCollisionWithWall(dtTime).x;
	MainCharacter::getInstance()->position += displayment;

	handleCollisionWithStair(dtTime);
	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}

void JumpState::handleCollisionWithStair(float dtTime)
{
	COLLIEVENTS coEvents;
	coEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Stair, dtTime);

	if (coEvents.size() == 1)
	{
		setState(MainCharacterState::Climb);
		Vector2 size = MainCharacter::getInstance()->animations->getAnimation(stateEnum)->getCurFrameSize();
		MainCharacter::getInstance()->position.x = coEvents[0]->gameObj->position.x - (size.x / 2 - 1);
	}
}

void JumpState::handleKeyInput(bool keyStates[])
{
	if (keyStates[DIK_LEFT] && !keyStates[DIK_RIGHT])
	{
		MainCharacter::getInstance()->setDirection(-1);
		MainCharacter::getInstance()->velocity.x = -MAINCHAR_MOVE_SPEED;
	}
	else if (keyStates[DIK_RIGHT] && !keyStates[DIK_LEFT])
	{
		MainCharacter::getInstance()->setDirection(1);
		MainCharacter::getInstance()->velocity.x = MAINCHAR_MOVE_SPEED;
	}
	else
		MainCharacter::getInstance()->velocity.x = 0;

	if (keyStates[DIK_SPACE])
		setState(MainCharacterState::StandAtk);

	if (keyStates[DIK_Z])
		setState(MainCharacterState::SpawnDart);
}
