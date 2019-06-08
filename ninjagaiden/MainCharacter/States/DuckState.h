#pragma once
#include "BaseState.h"

class DuckState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
};