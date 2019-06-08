#pragma once
#include "BaseState.h"

#define MAINCHAR_IMMORTAL_TIME 0.9f
#define MAINCHAR_IMMORTAL_BLINK_TIME 0.3f

class ImmortalState : public BaseState
{
/// Attributes
private:
	float immortalTime = MAINCHAR_IMMORTAL_TIME;
	float blinkTime = MAINCHAR_IMMORTAL_BLINK_TIME;

/// Methods
public:
	void render(Vector2 viewPosition);
	void handleKeyInput(bool keyStates[]);
	void update(float dtTime);
};