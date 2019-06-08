#pragma once
#include "BaseState.h"

class StandAtkState : public BaseState
{
/// Methods
private:
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
	void handleCollisionWithItems(float dtTime);
	void handleCollisionWithEnemies(float dtTime);
	void handleCollisionWithWeapons(float dtTime);
	Vector2 handleCollisionWithGround(float dtTime);
};