#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

/// Defines
#define DIRECTINPUT_VER 0x0800
#define KEYB_BUFFER_SIZE 1024
#define Color(r,g,b) D3DCOLOR_XRGB(r,g,b)

/// Typedefs
typedef D3DCOLOR Color;
typedef D3DXVECTOR2 Vector2; // typedef Vector 2 chiều
typedef LPDIRECT3DTEXTURE9 Texture; // typedef gọn lại kiểu Texture
typedef DIDEVICEOBJECTDATA KEYB_BUFFER[KEYB_BUFFER_SIZE]; // Typedef kiểu Buffer data cho Keyboard

/// Functions
Texture loadTexture(LPCWSTR filepath, Color transparent);
Vector2 getWindowClientSize(HWND window);
DIPROPDWORD createDeviceDataBuffer(DWORD bufferSize);

/// Classes
class DxGraphic; 
class DxInput; 
class DxMouse; 
class DxKeyboard; 
class DxSound; 

// Abstract Class MouseHandler để cho Class WinMouseHandler ở WinMain project kế thừa
class MouseHandler
{
/// Methods
public:
	virtual void onMouseState(DIMOUSESTATE* mouseState) = 0;
	virtual void onButtonPress(int button) = 0;
	virtual void onButtonRelease(int button) = 0;
};

// Abstract Class KeyboardHandler để cho Class WinKeyHandler ở WinMain project kế thừa
class KeyboardHandler 
{
/// Methods
public:
	virtual void onKeyState(bool keyStates[]) = 0;
	virtual void onKeyPress(int keycode) = 0;
	virtual void onKeyRelease(int keycode) = 0;
}; 