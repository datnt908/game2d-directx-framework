#pragma once
#include "BaseEnemy.h"

class MovingEnemy : public BaseEnemy
{
/// Attributes
protected:

/// Methods
private:

public:
	MovingEnemy(ObjKind kind, Vector2 leftbot, Vector2 moveSize);
	void updateMoveState(float dtTime);
	void updateAttkState(float dtTime);
};