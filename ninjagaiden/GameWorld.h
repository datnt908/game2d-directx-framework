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
	MainCharacter* mainChar;

/// Methods
private:
	bool loadResource();
	bool loadGameObjs(Stage stage);
	void updateCamera();
public:
	/// Common
	static GameWorld* getInstance();
	~GameWorld();
	bool initialize();
	void update(float dtTime);
	void render();
	/// For Game
	bool newGame();
	void respawn();
	void nextStage();
};