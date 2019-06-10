#include "DxGraphic.h"
#include "collisionHelper.h"
#include "Sprite.h"
#include "BaseTileMap.h"

BaseTileMap::BaseTileMap()
{
	spriteSize = Vector2(0.f, 0.f);
}

BaseTileMap::~BaseTileMap()
{
	for (auto sprite : spriteSet)
		delete sprite;
}

bool BaseTileMap::loadSpriteSet(Texture texture, Vector2 spriteSize)
{
	if (texture == NULL) return false;
	if (spriteSize.x <= 0.f || spriteSize.y <= 0.f) return false;
	this->spriteSize = spriteSize;
	int tilesetCols = (int)getTextureSize(texture).x / (int)spriteSize.x;
	int tilesetRows = (int)getTextureSize(texture).y / (int)spriteSize.y;
	if (tilesetCols * tilesetRows == 0) return false;
	for (auto sprite : spriteSet)
		delete sprite;
	spriteSet.clear();
	for (int i = 0; i < tilesetRows; i++)
		for (int j = 0; j < tilesetCols; j++)
		{
			RECT tempRect;
			tempRect.left = j * spriteSize.x;
			tempRect.right = (j + 1) * spriteSize.x;
			tempRect.top = i * spriteSize.y;
			tempRect.bottom = (i + 1) * spriteSize.y;
			spriteSet.push_back(new Sprite(texture, tempRect, Vector2(0.f, 0.f)));
		}
	return true;
}

bool BaseTileMap::loadMatrixMap(vector<INTS> matrixMap, int maxID)
{
	if (maxID >= spriteSet.size()) return false;
	this->matrixMap = matrixMap;
	size.x = matrixMap[0].size() * spriteSize.x;
	size.y = matrixMap.size() * spriteSize.y;
	return true;
}

void BaseTileMap::render(Vector2 camera)
{
	Vector2 clientSize = DxGraphic::getInstance()->clientSize;
	int fromCol, toCol, fromRow, toRow;

	Vector2 tempCamera= transformWorldToView(camera, position);

	fromCol = (int)tempCamera.x / (int)spriteSize.x;
	toCol = (int)(tempCamera.x + clientSize.x) / (int)spriteSize.x;
	fromRow = (int)tempCamera.y / (int)spriteSize.y;
	toRow = (int)(tempCamera.y + clientSize.y) / (int)spriteSize.y;

	fromCol = fromCol < 0 ? 0 : fromCol;
	fromRow = fromRow < 0 ? 0 : fromRow;
	toCol = toCol >= matrixMap[0].size() ? matrixMap[0].size() - 1 : toCol;
	toRow = toRow >= matrixMap.size() ? matrixMap.size() - 1 : toRow;

	Vector2 viewPos = transformWorldToView(position, camera);

	for (int i = fromRow; i <= toRow; i++)
		for (int j = fromCol; j <= toCol; j++)
		{
			Vector2 tempViewPos = viewPos + Vector2(j * spriteSize.x, i * spriteSize.y);
			spriteSet[matrixMap[i][j]]->render(tempViewPos);
		}
}

MOVEBOX BaseTileMap::getMoveBox(float dtTime)
{
	return MOVEBOX();
}
