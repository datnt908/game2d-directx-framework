#pragma once
#include "game2dHelper.h"

class Sprite
{
/// Attributes
private:
	RECT spriteRect;
	Texture texture;
	Vector2 size;
	Vector2 center;
	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotateMatrix;

/// Methods
public:
	Sprite(Texture texture, RECT rect, Vector2 center = Vector2(-1, -1));
	Vector2 getSize() { return size; }
	Vector2 getCenter() { return center; }
	void setRotate(float degrees);
	void setScale(Vector2 scaleRatio);
	void render(Vector2 viewPos);
};

