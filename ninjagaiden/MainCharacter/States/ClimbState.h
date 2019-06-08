#pragma once

class ClimbState;

#include "BaseState.h"
#include "MainCharacter.h"

class ClimbState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
	void handleCollisionWithStair(float dtTime);
};