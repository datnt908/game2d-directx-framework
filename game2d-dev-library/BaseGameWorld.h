#pragma once
#include "game2dHelper.h"

class BaseGameWorld
{
/// Attributes
protected:
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
	virtual ~BaseGameWorld();
	virtual bool initialize() = 0;
	virtual void update(float dtTime) = 0;
	virtual void render() = 0;
	/// Methods with Objects
	void addObject(int objKind, LPGAMEOBJ gameObj);
	void deleteObject(LPGAMEOBJ gameObj);
	GAMEOBJS_V* getInProcObjs(int objKind);
};