#pragma once

#define DIRECTINPUT_VER 0x0800
#define KEYB_BUFFER_SIZE 1024

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>

typedef D3DXVECTOR2 Vector2;
typedef D3DCOLOR Color;
typedef LPDIRECT3DTEXTURE9 Texture;
typedef DIDEVICEOBJECTDATA KEYB_BUFFER[KEYB_BUFFER_SIZE];

Texture loadTexture(LPCWSTR filepath, Color transparent);
Vector2 getWindowClientSize(HWND window);
DIPROPDWORD createDeviceDataBuffer(DWORD bufferSize);

class DxGraphic;
class DxInput;
class DxMouse;
class DxKeyboard;
class DxSound;

class MouseHandler
{
// Methods
public:
	virtual void onMouseState(DIMOUSESTATE* mouseState) = 0;
	virtual void onButtonPress(int button) = 0;
	virtual void onButtonRelease(int button) = 0;
};

class KeyboardHandler
{
// Methods
public:
	virtual void onKeyState(bool keyStates[]) = 0;
	virtual void onKeyPress(int keycode) = 0;
	virtual void onKeyRelease(int keycode) = 0;
};