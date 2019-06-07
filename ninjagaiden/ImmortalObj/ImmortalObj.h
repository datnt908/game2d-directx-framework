#pragma once
#include "GameObject.h"

class ImmortalObj : public GameObject
{
/// Methods
public:
	ImmortalObj(Vector2 position, Vector2 size);
	void update(float dtTime) {}
	void render(Vector2 camera) {}
};