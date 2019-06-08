#include "StandingEnemy.h"
#include "StraightWeapon.h"
#include "ParapolWeapon.h"
#include "MainCharacter.h"
#include "GameWorld.h"

StandingEnemy::StandingEnemy(ObjKind kind, Vector2 position) : BaseEnemy(kind, position)
{
	direction = -1;
	timeToAtk = ENEMIES_TIME_TO_ATK;
	state = EnemyState::ATTACK;
}

void StandingEnemy::updateMoveState(float dtTime)
{
	Vector2 mainPos = MainCharacter::getInstance()->position;
	if (mainPos.x > position.x) 
		direction = 1; 
	if (mainPos.x < position.x)
		direction = -1;
	timeToAtk -= dtTime;
	if (timeToAtk <= 0)
	{
		timeToAtk = ENEMIES_TIME_TO_ATK;
		state = EnemyState::ATTACK;
	}
}

void StandingEnemy::updateAttkState(float dtTime)
{
	timeToAtk -= dtTime;
	if (timeToAtk <= 0)
	{
		timeToAtk = ENEMIES_TIME_TO_ATK;
		BaseWeapon* weapon;
		switch (enemyKind)
		{
		case Enemy1:
			weapon = new ParapolWeapon();
			weapon->icon = WeaponIcon::Weapon1;
			weapon->velocity.x = direction * KNIFE_VELOCITY.x;
			weapon->velocity.y = KNIFE_VELOCITY.y;
			weapon->timeToDie = KINFE_TIME_TO_DIE;
			weapon->position.x = position.x;
			weapon->position.y = position.y + 15;
			GameWorld::getInstance()->addAlwayUpdateObject(ObjKind::ParabolWp, weapon);
			break;
		case Enemy3:
			weapon = new StraightWeapon();
			weapon->icon = WeaponIcon::Weapon3;
			weapon->velocity.x = direction * BULLET_VELOCITY.x;
			weapon->velocity.y = BULLET_VELOCITY.y;
			weapon->timeToDie = BULLECT_TIME_TO_DIE;
			weapon->position.x = position.x;
			weapon->position.y = position.y + 15;
			GameWorld::getInstance()->addAlwayUpdateObject(ObjKind::StraightWp, weapon);
			break;
		case Enemy6:
			weapon = new StraightWeapon();
			weapon->icon = WeaponIcon::Weapon6;
			weapon->velocity.x = direction * BULLET_VELOCITY.x;
			weapon->velocity.y = BULLET_VELOCITY.y;
			weapon->timeToDie = BULLECT_TIME_TO_DIE;
			weapon->position.x = position.x;
			weapon->position.y = position.y + 15;
			GameWorld::getInstance()->addAlwayUpdateObject(ObjKind::StraightWp, weapon);
			break;
		default:
			break;
		}
		state = EnemyState::MOVE;
	}
}
