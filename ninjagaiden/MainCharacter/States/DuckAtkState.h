#pragma once
#include "BaseState.h"

class DuckAtkState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
	void handleCollisionWithEnemiesAndWeapons(float dtTime);
	void handleCollisionWithBoss(float dtTime);
};