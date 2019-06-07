#include "Node.h"
#include "SpacePartitioning.h"

SpacePartitioning::~SpacePartitioning()
{
	for (auto cell : cells)
		delete cell;
}

void SpacePartitioning::loadFromFile(string filepath, Vector2 mapPos)
{
	STRINGS gridInfoLines = readFileText(filepath);
	for (unsigned int i = 1; i < gridInfoLines.size(); i++)
	{
		Node* tempnode = new Node();
		tempnode->loadFromString(gridInfoLines[i], mapPos);
		cells.push_back(tempnode);
	}
}

INTS SpacePartitioning::getObjIDsInView(Vector2 camera, Vector2 clientSize)
{
	INTS objIDs;
	for (auto cell : cells)
		objIDs = getUnionInt(cell->getObjIDsInView(camera, clientSize), objIDs);
	return objIDs;
}
