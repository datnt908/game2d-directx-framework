#pragma once
#include "DxHelper.h"

#define DIRECTINPUT_VER 0x0800

class DxInput
{
/// Attributes
private:
	static DxInput* instance;
	DxMouse* directxMouse;
	DxKeyboard* directxKeyb;
	LPDIRECTINPUT8 directxInput;

/// Methods
private:
	DxInput();
	bool initializeInputDevice();
public:
	static DxInput* getInstance();
	~DxInput();
	bool initializeMouse(MouseHandler* mouseHandler);
	bool initializeKeyb(KeyboardHandler* keybHandler);
	LPDIRECTINPUT8 getDirectInput();
	void processInput();
};