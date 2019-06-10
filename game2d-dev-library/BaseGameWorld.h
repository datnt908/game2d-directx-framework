#pragma once
#include "game2dHelper.h"
#include "SpacePartitioning.h"

class BaseGameWorld
{
/// Attributes
private:
	INTS alwayUpdate;
protected:
	SPACE spacePart;
	GAMEOBJS_U gameObjects; 
	GAMEOBJS_M inProcObjs;	
public:
	Vector2 camera;

/// Methods
protected:
	void updateInProcObjsList();
public:
	BaseGameWorld();
	virtual ~BaseGameWorld();
	virtual bool initialize() = 0;
	virtual void update(float dtTime) = 0;
	virtual void render() = 0;
	void addAlwayUpdateObject(int objKind, LPGAMEOBJ gameObj);
	void deleteObject(LPGAMEOBJ gameObj);
	GAMEOBJS_V* getInProcObjs(int objKind);
};