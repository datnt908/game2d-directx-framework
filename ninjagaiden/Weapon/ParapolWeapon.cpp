#include "ParapolWeapon.h"
#include "GameWorld.h"

void ParapolWeapon::update(float dtTime)
{
	timeToDie -= dtTime;
	if (timeToDie <= 0)
	{
		GameWorld::getInstance()->deleteObject(this);
		return;
	}

	velocity.y += dtTime * -FALL_SPEED;
	position += dtTime * velocity;
}
