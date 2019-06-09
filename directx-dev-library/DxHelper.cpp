#include "DxHelper.h"
#include "DxGraphic.h"

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