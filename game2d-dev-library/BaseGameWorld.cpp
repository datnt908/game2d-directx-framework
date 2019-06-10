#include "DxGraphic.h"
#include "BaseGameWorld.h"
#include "GameObject.h"

void BaseGameWorld::updateInProcObjsList()
{
	Vector2 clientSize = DxGraphic::getInstance()->clientSize;
	INTS objIDs = spacePart.getObjIDsInView(camera, clientSize);
	inProcObjs.clear();

	for (auto objID : objIDs)
		if (gameObjects[objID] != NULL)
			inProcObjs[objID / OBJ_KIND_WEIGHT].push_back(gameObjects[objID]);
		else
			gameObjects.erase(objID);

	for(unsigned int i = 0; i < alwayUpdate.size(); i++)
		if(gameObjects[alwayUpdate[i]] != NULL)
			inProcObjs[alwayUpdate[i] / OBJ_KIND_WEIGHT].push_back(gameObjects[alwayUpdate[i]]);
		else
		{
			alwayUpdate.erase(alwayUpdate.begin() + i);
			gameObjects.erase(alwayUpdate[i]);
		}
}

BaseGameWorld::BaseGameWorld()
{
	camera = DxGraphic::getInstance()->clientSize;
	camera.x = 0.f;
}

BaseGameWorld::~BaseGameWorld()
{
	for (auto iterator : gameObjects)
		delete iterator.second;
}

void BaseGameWorld::addAlwayUpdateObject(int objKind, LPGAMEOBJ gameObj)
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
	alwayUpdate.push_back(objID);
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
		for (unsigned int i = 0; i < inProcObjs[objKind].size(); i++)
			if (inProcObjs[objKind][i] == gameObj)
			{
				inProcObjs[objKind].erase(inProcObjs[objKind].begin() + i);
				break;
			}
		for(unsigned int i = 0; i < alwayUpdate.size(); i++)
			if (alwayUpdate[i] == objID)
			{
				alwayUpdate.erase(alwayUpdate.begin() + i);
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
