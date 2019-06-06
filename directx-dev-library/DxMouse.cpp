#include "DxGraphic.h"
#include "DxInput.h"
#include "DxMouse.h"

void DxMouse::collectState()
{
	HRESULT result = inputMouse->GetDeviceState(sizeof(mouseStates), (LPVOID)&mouseStates);
	if (FAILED(result))
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			inputMouse->Acquire();
}

DxMouse::~DxMouse()
{
	if (inputMouse != NULL)
	{
		inputMouse->Unacquire();
		inputMouse->Release();
	}
}

bool DxMouse::initialize(MouseHandler * mouseHandler)
{
	HWND hWnd = DxGraphic::getInstance()->window;
	LPDIRECTINPUT8 directInput = DxInput::getInstance()->getDirectInput();
	HRESULT result = directInput->CreateDevice(GUID_SysMouse, &inputMouse, NULL);
	if (result != DI_OK)
		return false;
	result = inputMouse->SetDataFormat(&c_dfDIMouse);
	result = inputMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	result = inputMouse->Acquire();
	this->mouseHandler = mouseHandler;
	return true;
}

void DxMouse::processInput()
{
	collectState();

	if (mouseHandler != NULL)
	{
		mouseHandler->onMouseState(&mouseStates);

		for (int i = 0; i < 4; i++)
		{
			if ((mouseStates.rgbButtons[i] & 0x80) > 0)
				mouseHandler->onButtonPress(i);
			else
				mouseHandler->onButtonRelease(i);
		}
	}
}
