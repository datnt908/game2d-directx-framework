#pragma once
#include "game2dHelper.h"
#include "GameObject.h"

class BaseTileMap : public GameObject
{
/// Attributes
protected:
	Vector2 spriteSize;
	SPRITES spriteSet;
	vector<INTS> matrixMap;

/// Methods
protected:
	bool loadSpriteSet(Texture texture, Vector2 spriteSize);
	bool loadMatrixMap(vector<INTS> matrixMap, int maxID);
public:
	virtual ~BaseTileMap();
	virtual bool loadResource() = 0;
	virtual void update(float dtTime) = 0;
	virtual void render(Vector2 camera);
	MOVEBOX getMoveBox(float dtTime);
};