#include <dinput.h>
#include "DuckState.h"

void DuckState::handleKeyInput(bool keyStates[])
{
	if (keyStates[DIK_LEFT] && !keyStates[DIK_RIGHT])
		MainCharacter::getInstance()->setDirection(-1);
	else if (keyStates[DIK_RIGHT] && !keyStates[DIK_LEFT])
		MainCharacter::getInstance()->setDirection(1);

	if (!keyStates[DIK_DOWN])
		setState(MainCharacterState::Idle);

	if (keyStates[DIK_SPACE])
		setState(MainCharacterState::DuckAtk);
}

void DuckState::update(float dtTime)
{
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemies(dtTime);
	handleCollisionWithWeapons(dtTime);
}