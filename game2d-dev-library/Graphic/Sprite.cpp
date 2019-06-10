#include "DxGraphic.h"
#include "Sprite.h"

Sprite::Sprite(Texture texture, RECT rect, Vector2 center)
{
	this->texture = texture;
	this->spriteRect = rect;
	if (center == Vector2(-1.f, -1.f))
	{
		center.x = (rect.right - rect.left) / 2.f;
		center.y = (rect.bottom - rect.top) / 2.f;
	}
	this->center = center;
	setRotate(0.f);
	setScale(Vector2(1.f, 1.f));
}

void Sprite::setRotate(float degrees)
{
	D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(degrees));
}

void Sprite::setScale(Vector2 scaleRatio)
{
	D3DXMatrixScaling(&scaleMatrix, scaleRatio.x, scaleRatio.y, 1.f);
	size.x = (spriteRect.right - spriteRect.left) * abs(scaleRatio.x);
	size.y = (spriteRect.bottom - spriteRect.top) * abs(scaleRatio.y);
}

void Sprite::render(Vector2 viewPos)
{
	LPD3DXSPRITE spriteHandler = DxGraphic::getInstance()->getSpriteHandler();
	D3DXMATRIX translateMatrix;
	D3DXMatrixTranslation(&translateMatrix, viewPos.x, viewPos.y, 0.f);
	spriteHandler->SetTransform(&(rotateMatrix * scaleMatrix * translateMatrix));
	spriteHandler->Draw(
		texture,
		&spriteRect,
		&D3DXVECTOR3(center.x, center.y, 0.f),
		NULL,
		Color(255, 255, 255)
	);
}
