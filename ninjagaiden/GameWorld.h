#pragma once
#include "BaseGameWorld.h"
#include "ninjagaidenHelper.h"

class GameWorld : public BaseGameWorld
{
/// Attributes
private:
	static GameWorld* instance;
	TileMap* tileMap;

/// Methods
private:
	bool loadResource();
public:
	/// Common
	static GameWorld* getInstance();
	bool initialize();
	void update(float dtTiem);
	void render();
};