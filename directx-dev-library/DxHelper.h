#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

/// Defines
#define Color(r,g,b) D3DCOLOR_XRGB(r,g,b)

/// Typedefs
typedef D3DCOLOR Color;
typedef D3DXVECTOR2 Vector2;
typedef LPDIRECT3DTEXTURE9 Texture;

/// Functions
Texture loadTexture(LPCWSTR filepath, Color transparent);

/// Classes
class DxGraphic; 
class DxInput; 
class DxMouse; 
class DxKeyboard; 
class DxSound; 

class MouseHandler
{
/// Methods
public:
	virtual void onMouseState(DIMOUSESTATE* mouseState) = 0;
	virtual void onButtonPress(int button) = 0;
	virtual void onButtonRelease(int button) = 0;
};

class KeyboardHandler 
{
/// Methods
public:
	virtual void onKeyState(bool keyStates[]) = 0;
	virtual void onKeyPress(int keycode) = 0;
	virtual void onKeyRelease(int keycode) = 0;
}; 