#include "BoundaryBox.h"

BOX BoundaryBox::getBox()
{
	BOX result;

	if (dtPosition.x >= 0)
	{
		result.position.x = position.x;
		result.size.x = dtPosition.x + size.x;
	}
	else
	{
		result.position.x = position.x + dtPosition.x;
		result.size.x = size.x - dtPosition.x;
	}

	if (dtPosition.y >= 0)
	{
		result.position.y = position.y;
		result.size.y = dtPosition.y + size.y;
	}
	else
	{
		result.position.y = position.y + dtPosition.y;
		result.size.y = size.y - dtPosition.y;
	}

	return result;
}
