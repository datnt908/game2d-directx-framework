﻿#pragma once
#include "InteractiveObj.h"

#define MAINCHAR_MOVE_SPEED 75
#define MAINCHAR_JUMP_SPEED 200
#define MAINCHAR_REVERSE_SPEED 10
#define MAINCHAR_TIME_SPAWN_WP 3.f
#define BLUEDART_SPEED 250
#define BLUEDART_TIMETODIE 2.f
#define BLUEDART_CONSUM 3
#define ORANGEDART_SPEED 200
#define ORANGEDART_TIMETODIE 4.f
#define ORANGEDART_CONSUM 5
#define DT_POSITION_SPAWN_WP Vector2(10, 20)

class BaseState;
class IdleState;
class MoveState;
class DuckState;
class JumpState;
class ClimbState;
class DuckAtkState;
class StandAtkState;
class SpawnDartState;
class ImmortalState;
class BaseWeapon;

class MainCharacter : public InteractiveObj
{
	friend class BaseState;
	friend class IdleState;
	friend class MoveState;
	friend class DuckState;
	friend class JumpState;
	friend class ClimbState;
	friend class DuckAtkState;
	friend class StandAtkState;
	friend class SpawnDartState;
	friend class ImmortalState;

/// Attributes
private:
	static MainCharacter* instance;
	int direction;
	BaseState* state;
	BaseWeapon* weapon;
	LPANIS animations;
public:
	int health;

/// Methods
private:
	MainCharacter() {}
	COLLIEVENTS getColliWithObjsByKind(int objKind, float dtTime);
	void updateWeapon(float dtTime);
public:
	/// Common
	static MainCharacter* getInstance();
	~MainCharacter();
	void update(float dtTime);
	void render(Vector2 camera);
	MOVEBOX getMoveBox(float dtTime);
	/// Additional
	void initialize();
	bool loadResource();
	void setDirection(int direction);
	void handleKeyInput(bool keyStates[]);
};