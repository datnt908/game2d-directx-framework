#pragma once

#include "DxHelper.h"

// Class DxKeyboard dành cho xử lý người dùng input tín hiệu Keyboard
class DxKeyboard
{
/// Attributes
private:
	LPDIRECTINPUTDEVICE8 inputKeyb;
	KeyboardHandler* keybHandler;
	BYTE keyStates[256];
	KEYB_BUFFER keyEvents;

/// Methods
private:
	void collectState();
	void collectBuffer();
public:
	~DxKeyboard();
	bool initialize(KeyboardHandler* keybHandler);
	void processInput();
};