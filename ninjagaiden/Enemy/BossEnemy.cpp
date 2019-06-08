#include <ctime>
#include "DxSound.h"
#include "TextureCollection.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "BossEnemy.h"
#include "Scoreboard.h"
#include "StraightWeapon.h"
#include "GameWorld.h"

Vector2 BossEnemy::handleCollisionWithGround(float dtTime)
{
	velocity.y += -FALL_SPEED * dtTime;
	Vector2 displayment = dtTime * velocity;

	COLLIEVENTS coEvents;
	calculateColli(GameWorld::getInstance()->getInProcObjs(ObjKind::Ground), dtTime, coEvents);

	for (auto coEvent : coEvents)
		if (coEvent->normal.y == 1)
		{
			displayment.y *= coEvent->colliTime;
			velocity.y = 0;
		}

	return displayment;
}

void BossEnemy::updateMoveState(float dtTime)
{
	timeToBeAtk -= dtTime;
	position.x += (int)(dtTime * velocity.x);
	position.y += handleCollisionWithGround(dtTime).y;

	// Change state
	if (velocity.y == 0)
	{
		velocity.x = -velocity.x;
		velocity.y = BOSSENE_VELOCITY.y;
		direction = -direction;
		state = EnemyState::ATTACK;
		numOfBullet = BOSSENE_NUM_OF_BULLET;
	}
}

void BossEnemy::updateAttkState(float dtTime)
{
	timeToBeAtk -= dtTime;
	waitTime -= dtTime;
	if (waitTime <= 0)
	{
		waitTime = BOSSENE_WAITTIME;
		state = EnemyState::MOVE;
		DxSound::getInstance()->playSound(BOSS_JUMP_SOUND_ID);
	}
	else if (0.9 <= waitTime && waitTime <= 1.1)
	{
		if (numOfBullet == 0) return;
		numOfBullet--;
		BaseWeapon * bullet = new StraightWeapon();
		bullet->icon = WeaponB;
		bullet->position.x = position.x;
		bullet->position.y = position.y + 25 + rand() % 15;
		bullet->timeToDie = 2.f;
		bullet->velocity.x = direction * 100;
		GameWorld::getInstance()->addAlwayUpdateObject(ObjKind::StraightWp, bullet);
	}
}

BossEnemy::BossEnemy(Vector2 leftbot_wP, Vector2 moveSize) : BaseEnemy(ObjKind::Boss, leftbot_wP)
{
	position.x = leftbot_wP.x + moveSize.x - 10;
	position.y = leftbot_wP.y;
	direction = -1;
	velocity = BOSSENE_VELOCITY;
	waitTime = BOSSENE_WAITTIME;
	numOfBullet = BOSSENE_NUM_OF_BULLET;
	timeToDie = BOSSENE_TIMETODIE;
	health = MAX_HEALTH;
	timeToBeAtk = BOSSENE_TIMETO_BEATTACKED;
}

void BossEnemy::onCollision()
{
	if (timeToBeAtk > 0) return;
	health--;
	if (health == 0)
	{
		state = EnemyState::DEAD;
		DxSound::getInstance()->playSound(BOSS_DIE_SOUND_ID);
		Scoreboard::getInstance()->score += BOSSENE_SCORE;
	}
	Scoreboard::getInstance()->enemyHealth = health;
	timeToBeAtk = BOSSENE_TIMETO_BEATTACKED;
}

void BossEnemy::render(Vector2 camera)
{
	Vector2 viewPos = transformWorldToView(position, camera);
	switch (state)
	{
	case MOVE:
		anicollectS[ObjKind::Boss]->getAnimation(state)->setScale(Vector2(direction, 1));
		anicollectS[ObjKind::Boss]->getAnimation(state)->render(viewPos);
		break;
	case ATTACK:
		anicollectS[ObjKind::Boss]->getAnimation(state)->setScale(Vector2(direction, 1));
		anicollectS[ObjKind::Boss]->getAnimation(state)->render(viewPos);
		break;
	case DEAD:
		anicollectS[ObjKind::Boss]->getAnimation(EnemyState::ATTACK)->setScale(Vector2(direction, 1));
		anicollectS[ObjKind::Boss]->getAnimation(EnemyState::ATTACK)->render(viewPos);
		srand(time(NULL));
		int deltax, deltay;
		viewPos.y -= 20;
		deltax = rand() % 41 - 20; deltay = rand() % 41 - 20;
		anicollectS[ENEMIES_DYING_ANIS_ID]->getAnimation(1)->render(viewPos + Vector2(deltax, deltay));
		deltax = rand() % 41 - 20; deltay = rand() % 41 - 20;
		anicollectS[ENEMIES_DYING_ANIS_ID]->getAnimation(1)->render(viewPos + Vector2(deltax, deltay));
		deltax = rand() % 41 - 20; deltay = rand() % 41 - 20;
		anicollectS[ENEMIES_DYING_ANIS_ID]->getAnimation(1)->render(viewPos + Vector2(deltax, deltay));
		break;
	default:
		break;
	}
}