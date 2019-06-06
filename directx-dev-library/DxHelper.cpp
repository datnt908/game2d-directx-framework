#include "DxHelper.h"

Vector2 getWindowClientSize(HWND window)
{
	Vector2 windowSize;
	RECT windowRect;
	GetClientRect(window, &windowRect);
	windowSize.x = (float)windowRect.right - windowRect.left;
	windowSize.y = (float)windowRect.bottom - windowRect.top;
	return windowSize;
}

DIPROPDWORD createDeviceDataBuffer(DWORD bufferSize)
{
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = bufferSize;
	return dipdw;
}

