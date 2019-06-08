#pragma once
#include "BaseWeapon.h"

#define CYCLE_TIME 1.f

class BoomerangWeapon : public BaseWeapon
{
/// Attributes
private:
	float cycle = CYCLE_TIME;
	Vector2 center;
public:
	Vector2 elipSize = Vector2(80, 10);
/// Method
public:
	void update(float dtTime);
};