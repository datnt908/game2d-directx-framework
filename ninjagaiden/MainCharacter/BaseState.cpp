#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
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
#include "MainCharacter.h"
#include "Item.h"
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

void BaseState::handleCollisionWithBoss(float dtTime)
{
	
}

void OnEndAttackAnimation()
{
	if (BaseState::stateEnum == MainCharacterState::StandAtk)
		BaseState::setState(MainCharacterState::Jump);
	else if (BaseState::stateEnum == MainCharacterState::DuckAtk)
		BaseState::setState(MainCharacterState::Duck);
}

void BaseState::setDeadState()
{
	if (Scoreboard::getInstance()->players)
		GameWorld::getInstance()->respawn();
	else
		GameWorld::getInstance()->newGame();
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
		if (coEvent->normal.y == 1)
		{
			displayment.y *= coEvent->colliTime;
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
	printBndBoxOutput(getBndBox(dtTime));
	if (tempVelocity.x != 0)
		int a = 1;
	COLLIEVENTS coEvents =
		MainCharacter::getInstance()->getColliWithObjsByKind(ObjKind::Wall, dtTime);

	

	for (auto coEvent : coEvents)
		if (coEvent->normal.x != 0)
			displayment.x *= coEvent->colliTime;
		else if (coEvent->colliTime == 0 && coEvent->normal == Vector2(0, 0))
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
		((Item*)(coEvent->gameObj))->onColliWithMainChar(false);
}

void BaseState::handleCollisionWithEnemiesAndWeapons(float dtTime)
{
	
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
		break;
	case DuckAtk:
		MainCharacter::getInstance()->state = &BaseState::duckatking;
		break;
	case Jump:
		MainCharacter::getInstance()->state = &BaseState::jumping;
		break;
	case Climb:
		MainCharacter::getInstance()->state = &BaseState::climbing;
		MainCharacter::getInstance()->velocity = Vector2(0, 0);
		break;
	case Immortal:
		setImmortalState();
		break;
	case Dead:
		setDeadState();
		return;
	}
	stateEnum = state;
}

BndBox BaseState::getBndBox(float dtTime)
{
	BndBox bb;
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

