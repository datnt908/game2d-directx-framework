#include "DxGraphic.h"
#include "DxInput.h"
#include "DxKeyboard.h"

void DxKeyboard::collectState()
{
	HRESULT result = inputKeyb->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(result))
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			inputKeyb->Acquire();
}

void DxKeyboard::collectBuffer()
{
	DWORD dwElements = KEYB_BUFFER_SIZE;
	HRESULT result = inputKeyb->GetDeviceData(
		sizeof(DIDEVICEOBJECTDATA),
		keyEvents,
		&dwElements,
		0
	);
}

DxKeyboard::~DxKeyboard()
{
	if (inputKeyb != NULL)
	{
		inputKeyb->Unacquire();
		inputKeyb->Release();
	}
}

bool DxKeyboard::initialize(KeyboardHandler * keybHandler)
{
	HWND hWnd = DxGraphic::getInstance()->window;
	LPDIRECTINPUT8 directInput = DxInput::getInstance()->getDirectInput();
	HRESULT result = directInput->CreateDevice(GUID_SysKeyboard, &inputKeyb, NULL);
	if (result != DI_OK)
		return false;
	result = inputKeyb->SetDataFormat(&c_dfDIKeyboard);
	result = inputKeyb->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD deviceDataBuffer = createDeviceDataBuffer(KEYB_BUFFER_SIZE);
	result = inputKeyb->SetProperty(DIPROP_BUFFERSIZE, &deviceDataBuffer.diph);
	if (result != DI_OK)
		return false;

	result = inputKeyb->Acquire();
	this->keybHandler = keybHandler;
	return true;
}

void DxKeyboard::processInput()
{
	collectState();
	bool keystates[256];
	for (int i = 0; i < 256; i++)
		keystates[i] = (keyStates[i] & 0x80) > 0;

	collectBuffer();
	if (keybHandler != NULL)
	{
		keybHandler->onKeyState(keystates);

		for (DWORD i = 0; i < KEYB_BUFFER_SIZE; i++)
		{
			int keycode = keyEvents[i].dwOfs;
			int keystate = keyEvents[i].dwData;
			if ((keystate & 0x80) > 0)
				keybHandler->onKeyPress(keycode);
			else
				keybHandler->onKeyRelease(keycode);
		}
	}
}
