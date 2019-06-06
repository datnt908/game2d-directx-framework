#pragma once

#include "DxHelper.h"

class WinKeyHandler : public KeyboardHandler
{
public:
	void onKeyState(bool keyStates[]);
	void onKeyPress(int keycode);
	void onKeyRelease(int keycode);
};

class WinMouseHandler : public MouseHandler
{
public:
	void onMouseState(DIMOUSESTATE* mouseState);
	void onButtonPress(int button);
	void onButtonRelease(int button);
};