#include "GameWorld.h"
#include "ImmortalObj.h"

GameWorld* GameWorld::instance = NULL;

GameWorld * GameWorld::getInstance()
{
	if (instance == NULL)
		instance = new GameWorld();
	return instance;
}

bool GameWorld::initialize()
{

	return true;
}

void GameWorld::update(float dtTiem)
{
}

void GameWorld::render()
{
}
