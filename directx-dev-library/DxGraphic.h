#pragma once

#include "DxHelper.h"

// Class DxGraphic dành cho xử lý đồ họa
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
	Vector2 clientSize; // Kích thước nội dung hiển thị của cửa sổ
	HWND window; // Con trỏ cửa sổ của chương trình

/// Methods
private:
	bool initializeDirect3d();
	bool initializeDevice(bool isFullscreen);
	D3DPRESENT_PARAMETERS createDx3dDeviceParam(HWND window, bool isFullscreen);

public:
	static DxGraphic* getInstance();
	~DxGraphic();
	bool initialize(HWND window, bool isFullscreen);
	LPD3DXSPRITE getSpriteHandler();
	friend Texture loadTexture(LPCWSTR filepath, Color transparent);
};