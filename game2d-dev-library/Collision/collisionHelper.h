#pragma once
#include "game2dHelper.h"

struct CollisionEvent {
	float colliTime;
	LPGAMEOBJ gameObj;
	Vector2 normal;
	CollisionEvent();
};
typedef struct CollisionEvent COLLIEVENT;
typedef vector<COLLIEVENT> COLLIEVENTS;

class MovementBox
{
/// Attributes
public:
	Vector2 position;
	Vector2 size;
	Vector2 dtPosition;

/// Methods
public:
	MovementBox();
	BNDBOX getBndBox(); 
};
typedef class MovementBox MOVEBOX;

float sweptAABB(MOVEBOX mObj, MOVEBOX sObj, Vector2 &normal);
