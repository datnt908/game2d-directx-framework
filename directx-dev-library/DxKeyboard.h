#pragma once

#include "DxHelper.h"

class DxKeyboard
{
// Attributes
private:
	LPDIRECTINPUTDEVICE8 inputKeyb;
	KeyboardHandler* keybHandler;
	BYTE keyStates[256];
	KEYB_BUFFER keyEvents;

// Methods
private:
	void collectState();
	void collectBuffer();

public:
	~DxKeyboard();
	bool initialize(KeyboardHandler* keybHandler);
	void processInput();
};