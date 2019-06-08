#pragma once
#include "BaseState.h"

class MoveState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
};
