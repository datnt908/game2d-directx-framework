#pragma once
#include "DxHelper.h"

class DxGraphic
{
	friend class GameWorld;
/// Attributes
private:
	static DxGraphic* instance;
	LPDIRECT3D9 direct3d;
	LPDIRECT3DDEVICE9 direct3dDevice;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;
public:
	Vector2 clientSize; 
	HWND window;

/// Methods
private:
	DxGraphic();
	bool initializeDirect3d();
	bool initializeDevice(bool isFullscreen);
	Vector2 getWindowClientSize(HWND window);
	D3DPRESENT_PARAMETERS createDx3dDeviceParam(bool isFullscreen);
public:
	static DxGraphic* getInstance();
	~DxGraphic();
	bool initialize(HWND window, bool isFullscreen);
	LPD3DXSPRITE getSpriteHandler();
	friend Texture loadTexture(LPCWSTR filepath, Color transparent);
};