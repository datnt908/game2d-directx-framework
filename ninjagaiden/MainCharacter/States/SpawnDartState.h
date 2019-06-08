#pragma once
#include "BaseState.h"

class SpawnDartState : public BaseState
{
/// Methods
public:
	void update(float dtTime);
	void handleKeyInput(bool keyStates[]);
	Vector2 handleCollisionWithGround(float dtTime);
};