#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "InteractiveObj.h"

COLLIEVENT * InteractiveObj::sweptAABBex(LPGAMEOBJ gameObj, float dtTime)
{
	BndBox sObjBBox = gameObj->getBndBox(dtTime);
	BndBox mObjBBox = this->getBndBox(dtTime);
	D3DXVECTOR2 normal;

	float time = sweptAABB(mObjBBox, sObjBBox, normal);

	COLLIEVENT* e = new CollisionEvent();
	e->colliTime = time;
	e->normal = normal;
	e->gameObj = gameObj;
	return e;
}

void InteractiveObj::calculateColli(GAMEOBJS_V * gameObjs, float dtTime, COLLIEVENTS & coEvents)
{
	for (auto gameObj : *gameObjs)
	{
		COLLIEVENT* e = sweptAABBex(gameObj, dtTime);
		if (e->colliTime == 1.0f && e->normal == D3DXVECTOR2(0, 0))
			delete e;
		else
			coEvents.push_back(e);
	}
}
