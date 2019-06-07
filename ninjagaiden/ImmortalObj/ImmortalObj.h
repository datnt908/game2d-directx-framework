#pragma once
#include "GameObject.h"

class ImmortalObj : public GameObject
{
/// Attributes


/// Methods
	void update(float dtTime);
	void render(Vector2 camera);
};