#include "collisionHelper.h"
#include "GameObject.h"

GameObject::GameObject()
{
	position = Vector2(0.f, 0.f);
	size = Vector2(0.f, 0.f);
	velocity = Vector2(0.f, 0.f);
}

MOVEBOX GameObject::getMoveBox(float dtTime)
{
	MOVEBOX bb;
	bb.position = position;
	bb.size = size;
	bb.dtPosition = velocity * dtTime;
	return bb;
}
