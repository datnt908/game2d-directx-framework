#pragma once
#include "BaseGameWorld.h"
#include "ninjagaidenHelper.h"

class GameWorld : public BaseGameWorld
{
/// Attributes
private:
	static GameWorld* instance;
	TileMap* tileMap;
	Scoreboard* scorebar;

/// Methods
private:
	bool loadResource();
	bool loadGameObjs(Stage stage);
public:
	/// Common
	static GameWorld* getInstance();
	~GameWorld();
	bool initialize();
	void update(float dtTime);
	void render();
	bool newGame();
};