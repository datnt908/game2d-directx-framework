#include <sstream>
#include <algorithm>
#include "Node.h"

// Load 1 line trong file phân hoạch không gian lên thành 1 node
// Hàm load này phụ thuộc vào cấu trúc file phân hoạch không gian
// Mô tả cấu trúc 1 line:
// id left top right bot <objIDs list>
void Node::loadFromString(string content, Vector2 mapPos)
{
	int left, top, right, bot, number;
	std::stringstream iss(content);

	iss >> id; iss >> left; iss >> top; iss >> right; iss >> bot;

	Vector2 lefttop = transformViewToWorld(Vector2(left, top), mapPos);
	Vector2 rightbot = transformViewToWorld(Vector2(right, bot), mapPos);

	nodeRect.left = lefttop.x;
	nodeRect.right = rightbot.x;
	nodeRect.top = lefttop.y;
	nodeRect.bottom = rightbot.y;

	while (iss >> number)
		objIDs.push_back(number);

	sort(objIDs.begin(), objIDs.end());
}

INTS Node::getObjIDsInView(Vector2 camera, Vector2 clientSize)
{
	BNDBOX viewBox, nodeBox;
	viewBox.position = camera;
	viewBox.size = clientSize;
	nodeBox.position.x = (float)nodeRect.left;
	nodeBox.position.y = (float)nodeRect.top;
	nodeBox.size.x = (float)abs(nodeRect.right - nodeRect.left);
	nodeBox.size.y = (float)abs(nodeRect.bottom - nodeRect.top);

	INTS objIDs;
	if (checkAABB_Box(nodeBox, viewBox))
		objIDs = this->objIDs;
	return objIDs;
}
