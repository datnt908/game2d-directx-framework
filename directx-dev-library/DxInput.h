#pragma once

#include "DxHelper.h"

class DxInput
{
// Attributes
private:
	static DxInput* instance;
	DxMouse* directxMouse;
	DxKeyboard* directxKeyb;
	LPDIRECTINPUT8 directxInput;

// Methods
private:
	bool initializeInputDevice();

public:
	static DxInput* getInstance();
	~DxInput();
	bool initializeMouse(MouseHandler* mouseHandler);
	bool initializeKeyb(KeyboardHandler* keybHandler);
	LPDIRECTINPUT8 getDirectInput();
	void processInput();
};