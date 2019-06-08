#pragma once
#include "BaseState.h"

class IdleState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
};
