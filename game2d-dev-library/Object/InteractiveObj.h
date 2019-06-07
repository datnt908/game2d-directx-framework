#pragma once
#include "GameObject.h"

class InteractiveObj : public GameObject
{
/// Methods
private:
	COLLIEVENT* sweptAABBex(LPGAMEOBJ gameObj, float dtTime);
public:
	void calculateColli(GAMEOBJS_V* gameObjs, float dtTime, COLLIEVENTS &coEvents);
};