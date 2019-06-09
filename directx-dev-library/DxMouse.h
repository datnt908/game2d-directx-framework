#pragma once
#include "DxHelper.h"

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
	DxMouse();
	~DxMouse();
	bool initialize(MouseHandler* mouseHandler);
	void processInput();
};

