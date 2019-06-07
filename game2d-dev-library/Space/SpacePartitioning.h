#pragma once
#include "game2dHelper.h"

class SpacePartitioning
{
/// Attributes
private:
	vector<Node*> cells;


/// Methods
public:
	~SpacePartitioning();
	void loadFromFile(string filepath, Vector2 mapPos);
	INTS getObjIDsInView(Vector2 camera, Vector2 clientSize);
};