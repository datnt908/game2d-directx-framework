#pragma once
#include "InteractiveObj.h"

#define MAINCHAR_MOVE_SPEED 75
#define MAINCHAR_JUMP_SPEED 200
#define MAINCHAR_REVERSE_SPEED 10

class BaseState;
class IdleState;
class MoveState;
class DuckState;
class JumpState;
class ClimbState;
class DuckAtkState;
class StandAtkState;
class ImmortalState;

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
	friend class ImmortalState;

/// Attributes
private:
	static MainCharacter* instance;
	int direction;
	BaseState* state;
	LPANIS animations;
public:
	int health;

/// Methods
private:
	MainCharacter() {}
	COLLIEVENTS getColliWithObjsByKind(int objKind, float dtTime);
public:
	/// Common
	static MainCharacter* getInstance();
	~MainCharacter();
	void update(float dtTime);
	void render(Vector2 camera);
	BndBox getBndBox(float dtTime);
	/// Additional
	void initialize();
	bool loadResource();
	void setDirection(int direction);
	void handleKeyInput(bool keyStates[]);
};