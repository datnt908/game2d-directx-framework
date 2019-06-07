#pragma once
#include "BaseGameWorld.h"

class GameWorld : public BaseGameWorld
{
/// Attributes
private:
	static GameWorld* instance;


/// Methods
public:
	static GameWorld* getInstance();
	bool initialize();
	void update(float dtTiem);
	void render();
};