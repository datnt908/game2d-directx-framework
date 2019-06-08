#include <dinput.h>
#include "MoveState.h"

void MoveState::update(float dtTime)
{
	handleCollisionWithGate(dtTime);
	handleCollisionWithGround(dtTime);

	Vector2 displayment = handleCollisionWithWall(dtTime);
	MainCharacter::getInstance()->position += displayment;

	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemiesAndWeapons(dtTime);
}

void MoveState::handleKeyInput(bool keyStates[])
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
	{
		setState(MainCharacterState::Idle);
		MainCharacter::getInstance()->velocity.x = 0;
	}

	if (keyStates[DIK_DOWN])
	{
		setState(MainCharacterState::Duck);
		MainCharacter::getInstance()->velocity.x = 0;
	}

	if (keyStates[DIK_SPACE])
	{
		setState(MainCharacterState::StandAtk);
		MainCharacter::getInstance()->velocity.x = 0;
	}

	if (keyStates[DIK_UP])
	{
		setState(MainCharacterState::Jump);
		MainCharacter::getInstance()->velocity.y = MAINCHAR_JUMP_SPEED;
	}
}
