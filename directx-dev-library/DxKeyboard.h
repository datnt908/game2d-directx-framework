#pragma once
#include "DxHelper.h"

#define KEYB_BUFFER_SIZE 1024

typedef DIDEVICEOBJECTDATA KEYB_BUFFER[KEYB_BUFFER_SIZE];

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
	DIPROPDWORD createDeviceDataBuffer(DWORD bufferSize);
	void collectState();
	void collectBuffer();
public:
	DxKeyboard();
	~DxKeyboard();
	bool initialize(KeyboardHandler* keybHandler);
	void processInput();
};