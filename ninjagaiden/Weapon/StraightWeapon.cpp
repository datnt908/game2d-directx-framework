#include "StraightWeapon.h"
#include "GameWorld.h"

void StraightWeapon::update(float dtTime)
{
	timeToDie -= dtTime;
	if (timeToDie <= 0)
	{
		GameWorld::getInstance()->deleteObject(this);
		return;
	}
	position += dtTime * velocity;
}