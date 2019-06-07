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
	GAMEOBJS_U gameObjects; // Store all Objects
	GAMEOBJS_M inProcObjs;	// In-Processing Objects
public:
	Vector2 camera;

/// Methods
protected:
	void updateInProcObjsList();
	void renderInProcObjs(int objKind);
public:
	/// Common methods
	BaseGameWorld();
	virtual ~BaseGameWorld();
	virtual bool initialize() = 0;
	virtual void update(float dtTime) = 0;
	virtual void render() = 0;
	/// Methods with Objects
	void addAlwayUpdateObject(int objKind, LPGAMEOBJ gameObj);
	void deleteObject(LPGAMEOBJ gameObj);
	GAMEOBJS_V* getInProcObjs(int objKind);
};