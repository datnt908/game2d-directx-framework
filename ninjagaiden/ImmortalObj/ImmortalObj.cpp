#include "ImmortalObj.h"

ImmortalObj::ImmortalObj(Vector2 position, Vector2 size)
{
	this->position = position;
	this->size = size;
	this->velocity = Vector2(0, 0);
}