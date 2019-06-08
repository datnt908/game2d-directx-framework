#include "StraightWeapon.h"
#include "GameWorld.h"

void StraightWeapon::update(float dtTime)
{
	BaseWeapon::update(dtTime);
	position += dtTime * velocity;
}