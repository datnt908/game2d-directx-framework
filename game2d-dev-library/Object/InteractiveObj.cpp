#include "collisionHelper.h"
#include "InteractiveObj.h"

COLLIEVENT InteractiveObj::sweptAABBex(LPGAMEOBJ gameObj, float dtTime)
{
	if (gameObj == NULL) return COLLIEVENT();
	MOVEBOX sObjBBox = gameObj->getMoveBox(dtTime);
	MOVEBOX mObjBBox = this->getMoveBox(dtTime);
	Vector2 normal(0.f, 0.f);

	float time = sweptAABB(mObjBBox, sObjBBox, normal);

	COLLIEVENT e;
	e.colliTime = time;
	e.normal = normal;
	e.gameObj = gameObj;
	return e;
}

void InteractiveObj::calculateColli(GAMEOBJS_V * gameObjs, float dtTime, COLLIEVENTS & coEvents)
{
	if (gameObjs == NULL) return;
	coEvents.clear();
	for (auto gameObj : *gameObjs)
	{
		COLLIEVENT e = sweptAABBex(gameObj, dtTime);
		if (e.colliTime != 1.0f || e.normal != Vector2(0.f, 0.f))
			coEvents.push_back(e);
	}
}
