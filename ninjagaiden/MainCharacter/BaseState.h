#pragma once
#include "MainCharacter.h"

enum MainCharacterState
{
	Idle = 0,
	Duck = 1,
	Move = 2,
	Jump = 5,
	Dead = 8,
	Climb = 6,
	DuckAtk = 4,
	StandAtk = 3,
	Immortal = 7
};

class IdleState;
class MoveState;
class DuckState;
class JumpState;
class ClimbState;
class DuckAtkState;
class StandAtkState;
class ImmortalState;

void OnEndAttackAnimation();

class BaseState
{
	friend void OnEndAttackAnimation();

/// Attributes
public:
	static MainCharacterState stateEnum;
	static IdleState idling;
	static MoveState moving;
	static DuckState ducking;
	static JumpState jumping;
	static ClimbState climbing;
	static DuckAtkState duckatking;
	static StandAtkState standatking;
	static ImmortalState immortaling;

/// Methods
private:
	static void setImmortalState();
	static void setDeadState();
protected:
	static void setState(MainCharacterState state);
	virtual void handleCollisionWithBoss(float dtTime);
	virtual void handleCollisionWithGate(float dtTime);
	virtual void handleCollisionWithWater(float dtTime);
	virtual void handleCollisionWithItems(float dtTime);
	virtual void handleCollisionWithEnemiesAndWeapons(float dtTime);
	virtual Vector2 handleCollisionWithWall(float dtTime);
	virtual Vector2 handleCollisionWithGround(float dtTime);
public:
	virtual BndBox getBndBox(float dtTime);
	virtual void render(Vector2 viewPos);
	virtual void update(float dtTime) = 0;
	virtual void handleKeyInput(bool keyStates[]) = 0;
};