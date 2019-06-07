#pragma once
#include "game2dHelper.h"

class Node
{
/// Attributes
private:
	int id;
	RECT nodeRect;
	INTS objIDs;

/// Methods
public:
	void loadFromString(string content, Vector2 mapPos);
	INTS getObjIDsInView(Vector2 camera, Vector2 clientSize);
};