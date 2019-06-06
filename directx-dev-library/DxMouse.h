#pragma once

#include "DxHelper.h"

// Class DxMouse dành cho xử lý người dùng input tín hiệu Mouse
class DxMouse
{
/// Attributes
private:
	LPDIRECTINPUTDEVICE8 inputMouse;
	MouseHandler* mouseHandler;
	DIMOUSESTATE mouseStates;

/// Methods
private:
	void collectState();

public:
	~DxMouse();
	bool initialize(MouseHandler* mouseHandler);
	void processInput();
};

