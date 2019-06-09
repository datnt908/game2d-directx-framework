#include "DxSound.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "collisionHelper.h"

#include "Scoreboard.h"
#include "BaseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "DuckState.h"
#include "JumpState.h"
#include "ClimbState.h"
#include "DuckAtkState.h"
#include "StandAtkState.h"
#include "ImmortalState.h"
#include "SpawnDartState.h"
#include "MainCharacter.h"
#include "Item.h"
#include "BaseEnemy.h"
#include "StraightWeapon.h"
#include "BoomerangWeapon.h"
#include "ParapolWeapon.h"
#include "GameWorld.h"

MainCharacterState BaseState::stateEnum = MainCharacterState::Jump;
IdleState BaseState::idling;
MoveState BaseState::moving;
DuckState BaseState::ducking;
JumpState BaseState::jumping;
ClimbState BaseState::climbing;
StandAtkState BaseState::standatking;
DuckAtkState BaseState::duckatking;
ImmortalState BaseState::immortaling;
SpawnDartState BaseState::spawningWp;

void OnEndAttackAnimation()
{
	if (BaseState::stateEnum == MainCharacterState::StandAtk)
		BaseState::setState(MainCharacterState::Jump);
	else if (BaseState::stateEnum == MainCharacterState::DuckAtk)
		BaseState::setState(MainCharacterState::Duck);
	else if (BaseState::stateEnum == MainCharacterState::SpawnDart)
		BaseState::setState(MainCharacterState::Jump);
}

void BaseState::setDeadState()
{
	if (Scoreboard::getInstance()->players)
		GameWorld::getInstance()->respawn();
	else
		GameWorld::getInstance()->newGame();
}

void BaseState::setSpawnWpState()
{
	MainCharacter* mainChar = MainCharacter::getInstance();
	BaseWeapon * weapon;
	if (mainChar->weapon != NULL) return;
	switch (Scoreboard::getInstance()->curItem)
	{
	case ItemKind::BlueDart:
		if (Scoreboard::getInstance()->items < BLUEDART_CONSUM)
			return;
		Scoreboard::getInstance()->items -= BLUEDART_CONSUM;
		weapon = new StraightWeapon();
		weapon->position.x = mainChar->position.x + mainChar->direction * DT_POSITION_SPAWN_WP.x;
		weapon->position.y = mainChar->position.y + DT_POSITION_SPAWN_WP.y;
		weapon->velocity.x = mainChar->direction * BLUEDART_SPEED;
		weapon->icon = WeaponIcon::WpBlueDart;
		weapon->timeToDie = BLUEDART_TIMETODIE;
		mainChar->weapon = weapon;
		break;
	case ItemKind::OrangeDart:
		if (Scoreboard::getInstance()->items < ORANGEDART_CONSUM)
			return;
		Scoreboard::getInstance()->items -= ORANGEDART_CONSUM;
		weapon = new BoomerangWeapon();
		weapon->timeToDie = ORANGEDART_TIMETODIE;
		weapon->icon = WeaponIcon::WpOraDart;
		mainChar->weapon = weapon;
		break;
	default:
		return;
	}
	mainChar->state = &BaseState::spawningWp;
	stateEnum = MainCharacterState::SpawnDart;
}

void BaseState::setImmortalState()
{
	MainCharacter::getInstance()->state = &BaseState::immortaling;
	MainCharacter::getInstance()->velocity =
		Vector2(-MainCharacter::getInstance()->direction * MAINCHAR_REVERSE_SPEED, 0);
	MainCharacter::getInstance()->health--;
	Scoreboard::getInstance()->mainHealth--;
	if (!MainCharacter::getInstance()->health)
		setState(MainCharacterState::Dead);
}

Vector2 BaseState::handleCollisionWithGround(float dtTime)
{
	MainCharacter::getInstance()->velocity.y += -FALL_SPEED * dtTime;
	Vector2 tempVelocity = MainCharacter::getInstance()->velocity;
	MainCharacter::getInstance()->velocity.x = 0;
	Vector2 displayment = dtTime * MainCharacter::getInstance()->velocity;

	COLLIEVENTS coEvents =
		MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Ground, dtTime);

	for (auto coEvent : coEvents)
		if (coEvent.normal.y == 1)
		{
			displayment.y *= coEvent.colliTime;
			MainCharacter::getInstance()->velocity.y = 0;
		}

	if(MainCharacter::getInstance()->velocity.y != 0)
		setState(MainCharacterState::Jump);

	MainCharacter::getInstance()->velocity.x = tempVelocity.x;
	return displayment;
}

Vector2 BaseState::handleCollisionWithWall(float dtTime)
{
	Vector2 tempVelocity = MainCharacter::getInstance()->velocity;
	MainCharacter::getInstance()->velocity.y = 0;
	Vector2 displayment = dtTime * MainCharacter::getInstance()->velocity;
	if (tempVelocity.x != 0)
		int a = 1;
	COLLIEVENTS coEvents =
		MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Wall, dtTime);
	
	for (auto coEvent : coEvents)
		if (coEvent.normal.x != 0)
			displayment.x *= coEvent.colliTime;
		else if (coEvent.colliTime == 0 && coEvent.normal == Vector2(0, 0))
			displayment.x = 0;

	MainCharacter::getInstance()->velocity = tempVelocity;
	return displayment;
}

void BaseState::handleCollisionWithGate(float dtTime)
{
	COLLIEVENTS coEvents;
	coEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Gate, dtTime);
	if (coEvents.size())
		GameWorld::getInstance()->nextStage();
}

void BaseState::handleCollisionWithWater(float dtTime)
{
	COLLIEVENTS coEvents;
	coEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Water, dtTime);
	if (coEvents.size())
		setState(MainCharacterState::Dead);
}

void BaseState::handleCollisionWithItems(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;

	tempCoEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Item1, dtTime);
	coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());
	tempCoEvents = MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Item2, dtTime);
	coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());

	for (auto coEvent : coEvents)
		((Item*)(coEvent.gameObj))->onColliWithMainChar(false);
}

void BaseState::handleCollisionWithEnemies(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;
	MainCharacter* mainChar = MainCharacter::getInstance();
	for (unsigned int i = 2; i <= 9; i++)
	{
		tempCoEvents = mainChar->getColliWithObjsByKind((ObjKind)i, dtTime);
		coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());
	}
	
	if (coEvents.size() != 0)
		setState(MainCharacterState::Immortal);
}

void BaseState::handleCollisionWithWeapons(float dtTime)
{
	COLLIEVENTS tempCoEvents;
	COLLIEVENTS coEvents;
	MainCharacter* mainChar = MainCharacter::getInstance();

	for (unsigned int i = 15; i <= 17; i++)
	{
		tempCoEvents = mainChar->getColliWithObjsByKind((ObjKind)i, dtTime);
		coEvents.insert(coEvents.end(), tempCoEvents.begin(), tempCoEvents.end());
	}

	for (auto coEvent : coEvents)
		((BaseWeapon*)(coEvent.gameObj))->onCollision();

	if (coEvents.size() != 0)
		setState(MainCharacterState::Immortal);
}

void BaseState::setState(MainCharacterState state)
{
	if (state == stateEnum) return;
	switch (state)
	{
	case Idle:
		MainCharacter::getInstance()->state = &BaseState::idling;
		break;
	case Duck:
		MainCharacter::getInstance()->state = &BaseState::ducking;
		break;
	case Move:
		MainCharacter::getInstance()->state = &BaseState::moving;
		break;
	case StandAtk:
		MainCharacter::getInstance()->state = &BaseState::standatking;
		DxSound::getInstance()->playSound(MAIN_ATTACK_SOUND_ID);
		break;
	case DuckAtk:
		MainCharacter::getInstance()->state = &BaseState::duckatking;
		DxSound::getInstance()->playSound(MAIN_ATTACK_SOUND_ID);
		break;
	case Jump:
		MainCharacter::getInstance()->state = &BaseState::jumping;
		DxSound::getInstance()->playSound(MAIN_JUMP_SOUND_ID);
		break;
	case Climb:
		MainCharacter::getInstance()->state = &BaseState::climbing;
		MainCharacter::getInstance()->velocity = Vector2(0, 0);
		break;
	case SpawnDart:
		setSpawnWpState();
		return;
	case Immortal:
		setImmortalState();
		DxSound::getInstance()->playSound(MAIN_ATTACKED_SOUNE_ID);
		break;
	case Dead:
		setDeadState();
		return;
	}
	stateEnum = state;
}

MOVEBOX BaseState::getMoveBox(float dtTime)
{
	MOVEBOX bb;
	Vector2 center;
	center = MainCharacter::getInstance()->animations->getAnimation(stateEnum)->getCurFrameCenter();
	bb.size = MainCharacter::getInstance()->animations->getAnimation(stateEnum)->getCurFrameSize();
	if (MainCharacter::getInstance()->direction == -1)
		center.x = bb.size.x - center.x;
	Vector2 positionTransfered = transformViewToWorld(center, Vector2(0, bb.size.y));
	bb.position = MainCharacter::getInstance()->position - positionTransfered;
	bb.dtPosition = MainCharacter::getInstance()->velocity * dtTime;
	return bb;
}

void BaseState::render(Vector2 viewPos)
{
	MainCharacter::getInstance()->animations->getAnimation(stateEnum)->render(viewPos);
}

