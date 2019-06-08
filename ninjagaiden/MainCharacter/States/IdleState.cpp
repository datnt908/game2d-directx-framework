#include <dinput.h>
#include "IdleState.h"
#include "MainCharacter.h"

void IdleState::update(float dtTime)
{
	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemiesAndWeapons(dtTime);
}

void IdleState::handleKeyInput(bool keyStates[])
{
	if (keyStates[DIK_LEFT] && !keyStates[DIK_RIGHT])
	{
		setState(MainCharacterState::Move);
		MainCharacter::getInstance()->setDirection(-1);
	}
	else if (keyStates[DIK_RIGHT] && !keyStates[DIK_LEFT])
	{
		setState(MainCharacterState::Move);
		MainCharacter::getInstance()->setDirection(1);
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