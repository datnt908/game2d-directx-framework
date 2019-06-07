#include "BoundaryBox.h"
#include "GameObject.h"

BndBox GameObject::getBndBox(float dtTime)
{
	BndBox bb;
	bb.position = this->position;
	bb.size = this->size;
	bb.dtPosition = this->velocity * dtTime;
	return bb;
}
