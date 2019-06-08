#include "ParapolWeapon.h"
#include "GameWorld.h"

void ParapolWeapon::update(float dtTime)
{
	BaseWeapon::update(dtTime);
	velocity.y += dtTime * -FALL_SPEED;
	position += dtTime * velocity;
}
