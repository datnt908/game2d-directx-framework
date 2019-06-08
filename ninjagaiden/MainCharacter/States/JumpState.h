#pragma once
#include "BaseState.h"

class JumpState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
	void handleCollisionWithStair(float dtTime);
};