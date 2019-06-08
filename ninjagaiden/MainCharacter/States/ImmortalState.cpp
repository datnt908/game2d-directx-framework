#include "Animation.h"
#include "AnimationCollection.h"
#include "ImmortalState.h"

void ImmortalState::render(Vector2 viewPosition)
{
	if(blinkTime >= MAINCHAR_IMMORTAL_BLINK_TIME / 2)
		MainCharacter::getInstance()->animations->getAnimation(stateEnum)->render(viewPosition);
}

void ImmortalState::handleKeyInput(bool keyStates[])
{
}

void ImmortalState::update(float dtTime)
{
	MainCharacter::getInstance()->position += dtTime * MainCharacter::getInstance()->velocity;
	immortalTime -= dtTime;
	blinkTime -= dtTime;
	if (immortalTime <= 0)
	{
		immortalTime = MAINCHAR_IMMORTAL_TIME;
		blinkTime = MAINCHAR_IMMORTAL_BLINK_TIME;
		setState(MainCharacterState::Jump);
	}
	if (blinkTime <= 0)
		blinkTime = MAINCHAR_IMMORTAL_BLINK_TIME;
}

