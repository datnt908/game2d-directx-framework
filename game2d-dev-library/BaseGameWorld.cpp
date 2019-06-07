#include "BaseGameWorld.h"

void BaseGameWorld::updateInProcObjsList()
{
}

void BaseGameWorld::renderInProcObjs(int objKind)
{			
}

BaseGameWorld::~BaseGameWorld()
{
	for (auto iterator : gameObjects)
		delete iterator.second;
}

void BaseGameWorld::deleteObject(LPGAMEOBJ gameObj)
{
	for(auto iterator : gameObjects)
		if (iterator.second == gameObj)
		{
			gameObjects.erase(iterator.first);
			break;
		}
	delete gameObj;
}

GAMEOBJS_V * BaseGameWorld::getInProcObjs(int objKind)
{
	if (inProcObjs.find(objKind) != inProcObjs.end())
		return &inProcObjs[objKind];
	return NULL;
}
