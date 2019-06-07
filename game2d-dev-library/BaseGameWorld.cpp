#include "BaseGameWorld.h"
#include "GameObject.h"

void BaseGameWorld::updateInProcObjsList()
{

}

void BaseGameWorld::renderInProcObjs(int objKind)
{			
	if (inProcObjs.find(objKind) != inProcObjs.end())
		for (auto obj : inProcObjs[objKind])
			if(obj != NULL) 
				obj->render(camera);
}

BaseGameWorld::~BaseGameWorld()
{
	for (auto iterator : gameObjects)
		delete iterator.second;
}

void BaseGameWorld::addObject(int objKind, LPGAMEOBJ gameObj)
{
	if (gameObj == NULL) return;
	int objID = objKind * OBJ_KIND_WEIGHT;
	for(unsigned int i = 0; i < OBJ_KIND_WEIGHT; i++)
		if (gameObjects[objID + i] == NULL)
		{
			objID += i;
			gameObjects[objID] = gameObj;
			break;
		}
	inProcObjs[objKind].push_back(gameObj);
}

void BaseGameWorld::deleteObject(LPGAMEOBJ gameObj)
{
	int objID = INT_MIN;
	int objKind = INT_MIN;

	for (auto iterator : gameObjects)
		if (iterator.second == gameObj)
		{
			objID = iterator.first;
			objKind = objID / OBJ_KIND_WEIGHT;
			break;
		}

	if (objID != INT_MIN)
	{
		gameObjects.erase(objID);
		if (inProcObjs.find(objKind) != inProcObjs.end())
			for (unsigned int i = 0; i < inProcObjs[objKind].size(); i++)
				if (inProcObjs[objKind][i] == gameObj)
				{
					inProcObjs[objKind].erase(inProcObjs[objKind].begin() + i);
					break;
				}
		delete gameObj;
	}
}

GAMEOBJS_V * BaseGameWorld::getInProcObjs(int objKind)
{
	if (inProcObjs.find(objKind) != inProcObjs.end())
		return &inProcObjs[objKind];
	return NULL;
}
