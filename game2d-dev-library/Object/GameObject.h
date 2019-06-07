#pragma once
#include "game2dHelper.h"

class GameObject
{
/// Attributes
public:
	Vector2 position;
	Vector2 size;
	Vector2 velocity;

/// Methods
public:
	virtual ~GameObject() {}
	virtual void update(float dtTime) = 0;
	virtual void render(Vector2 camera) = 0;
	virtual BndBox getBndBox(float dtTime);
};