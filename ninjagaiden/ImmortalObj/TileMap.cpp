
#include <sstream>
#include "TextureCollection.h"
#include "TileMap.h"

bool TileMap::loadResource()
{
	STRINGS matrixFileLines;
	vector<INTS> tempMapMatrix;
	Texture texture;
	TEXTURES* textures = TextureCollection::getInstance();
	switch (stage)
	{
	case _3_1:
		texture = textures->getTexture(STAGE_3_1_TEXTUREID);
		matrixFileLines = readFileText(STAGE_3_1_MATRIXFILE);
		break;
	case _3_2:
		texture = textures->getTexture(STAGE_3_2_TEXTUREID);
		matrixFileLines = readFileText(STAGE_3_2_MATRIXFILE);
		break;
	default:
		texture = textures->getTexture(STAGE_3_3_TEXTUREID);
		matrixFileLines = readFileText(STAGE_3_3_MATRIXFILE);
		break;
	}

	int maxID = INT_MIN;
	for (auto matrixFileLine : matrixFileLines)
	{
		INTS tempLine;
		int number;
		stringstream iss(matrixFileLine);
		while (iss >> number)
		{
			if (number > maxID) maxID = number;
			tempLine.push_back(number);
		}
		tempMapMatrix.push_back(tempLine);
	}

	if (!loadSpriteSet(texture, TILEMAP_SPRITE_SIZE))
		return false;

	if (!loadMatrixMap(tempMapMatrix, maxID))
		return false;

	return true;
}

bool TileMap::loadStage(Stage stage)
{
	this->stage = stage;
	this->position = MAP_POS;
	return loadResource();
}
