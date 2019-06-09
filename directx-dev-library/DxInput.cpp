#include "DxGraphic.h"
#include "DxInput.h"
#include "DxMouse.h"
#include "DxKeyboard.h"

DxInput* DxInput::instance = NULL;

DxInput::DxInput()
{
	directxInput = NULL;
	directxMouse = NULL;
	directxKeyb = NULL;
}

bool DxInput::initializeInputDevice()
{
	HWND window = DxGraphic::getInstance()->window;

	HRESULT result = DirectInput8Create(
		(HINSTANCE)GetWindowLong(window, GWL_HINSTANCE),
		DIRECTINPUT_VER,
		IID_IDirectInput8,
		(VOID**)&directxInput, NULL
	);

	if (result != DI_OK)
		return false;
	return true;
}

DxInput * DxInput::getInstance()
{
	if (instance == NULL)
		instance = new DxInput();
	return instance;
}

DxInput::~DxInput()
{
	if (directxKeyb != NULL)
		delete directxKeyb;
	if (directxMouse != NULL)
		delete directxMouse;
	if (directxInput != NULL)
		directxInput->Release();
}

bool DxInput::initializeMouse(MouseHandler * mouseHandler)
{
	if (directxInput == NULL)
		if (!initializeInputDevice())
			return false;
	directxMouse = new DxMouse();
	if (!directxMouse->initialize(mouseHandler))
		return false;
	return true;
}

bool DxInput::initializeKeyb(KeyboardHandler * keybHandler)
{
	if (directxInput == NULL)
		if (!initializeInputDevice())
			return false;
	directxKeyb = new DxKeyboard();
	if (!directxKeyb->initialize(keybHandler))
		return false;
	return true;
}

LPDIRECTINPUT8 DxInput::getDirectInput()
{
	return directxInput;
}

void DxInput::processInput()
{
	if (directxMouse != NULL)
		directxMouse->processInput();
	if (directxKeyb != NULL)
		directxKeyb->processInput();
}
