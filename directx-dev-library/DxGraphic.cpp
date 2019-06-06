#include "DxGraphic.h"

DxGraphic* DxGraphic::instance;

bool DxGraphic::initializeDirect3d()
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		return false;
	return true;
}

bool DxGraphic::initializeDevice(bool isFullscreen)
{
	D3DPRESENT_PARAMETERS parameter = createDx3dDeviceParam(window, isFullscreen);
	clientSize.x = (float)parameter.BackBufferWidth;
	clientSize.y = (float)parameter.BackBufferHeight;

	direct3d->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&parameter,
		&direct3dDevice
	);

	if (direct3dDevice == NULL)
		return false;
	return true;
}

DxGraphic * DxGraphic::getInstance()
{
	if (instance == NULL)
		instance = new DxGraphic();
	return instance;
}

DxGraphic::~DxGraphic()
{
	if (spriteHandler != NULL)
		spriteHandler->Release();
	if (backBuffer != NULL)
		backBuffer->Release();
	if (direct3dDevice != NULL)
		direct3dDevice->Release();
	if (direct3d != NULL)
		direct3d->Release();
}

bool DxGraphic::initialize(HWND window, bool isFullscreen)
{
	this->window = window;
	if (this->window == NULL)
		return false;
	
	if (!initializeDirect3d())
		return false;

	if (!initializeDevice(isFullscreen))
		return false;

	direct3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	direct3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	if (backBuffer == NULL)
		return false;

	D3DXCreateSprite(direct3dDevice, &spriteHandler);
	if (spriteHandler == NULL)
		return false;

	return true;
}

LPD3DXSPRITE DxGraphic::getSpriteHandler()
{
	return spriteHandler;
}

Texture loadTexture(LPCWSTR filepath, Color transparent)
{
	Texture texture;
	D3DXIMAGE_INFO imageInfo;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filepath, &imageInfo);
	if (result != D3D_OK)
		return NULL;

	result = D3DXCreateTextureFromFileEx(
		DxGraphic::getInstance()->direct3dDevice, 
		filepath,
		imageInfo.Width, imageInfo.Height,
		1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		transparent, &imageInfo, NULL, &texture
	);

	if (result != D3D_OK)
		return NULL;

	return texture;
}

D3DPRESENT_PARAMETERS DxGraphic::createDx3dDeviceParam(HWND window, bool isFullscreen)
{
	D3DXVECTOR2 windowSize;
	D3DPRESENT_PARAMETERS direct3dDeviceParameters;

	windowSize = getWindowClientSize(window);
	ZeroMemory(&direct3dDeviceParameters, sizeof(direct3dDeviceParameters));
	direct3dDeviceParameters.Windowed = (!isFullscreen);
	direct3dDeviceParameters.SwapEffect = D3DSWAPEFFECT_COPY;
	direct3dDeviceParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	direct3dDeviceParameters.BackBufferCount = 1;
	direct3dDeviceParameters.BackBufferWidth = (int)windowSize.x;
	direct3dDeviceParameters.BackBufferHeight = (int)windowSize.y;
	direct3dDeviceParameters.hDeviceWindow = window;

	return direct3dDeviceParameters;
}

