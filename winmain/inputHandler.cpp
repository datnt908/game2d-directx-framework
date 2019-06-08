#include "inputHandler.h"
#include "MainCharacter.h"

void WinKeyHandler::onKeyState(bool keyStates[])
{
	MainCharacter::getInstance()->handleKeyInput(keyStates);
}

void WinKeyHandler::onKeyPress(int keycode)
{
}

void WinKeyHandler::onKeyRelease(int keycode)
{
}

void WinMouseHandler::onMouseState(DIMOUSESTATE * mouseState)
{
}

void WinMouseHandler::onButtonPress(int button)
{
}

void WinMouseHandler::onButtonRelease(int button)
{
}
