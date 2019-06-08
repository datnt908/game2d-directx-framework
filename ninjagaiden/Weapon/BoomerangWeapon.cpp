#include "BoomerangWeapon.h"
#include "MainCharacter.h"
#include "GameWorld.h"

void BoomerangWeapon::update(float dtTime)
{
	timeToDie -= dtTime;
	if (timeToDie <= 0)
	{
		GameWorld::getInstance()->deleteObject(this);
		return;
	}
	MainCharacter* mainChar = MainCharacter::getInstance();
	cycle = cycle <= 0 ? CYCLE_TIME : cycle - dtTime;
	center = mainChar->position + DT_POSITION_SPAWN_WP;
	float radian = D3DXToRadian(360.f) * cycle / CYCLE_TIME;
	position.x = center.x + elipSize.x * sin(radian);
	position.y = center.y + elipSize.y * cos(radian);
}
