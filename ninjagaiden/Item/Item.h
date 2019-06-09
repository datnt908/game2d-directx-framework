#pragma once
#include "InteractiveObj.h"
#include "ninjagaidenHelper.h"

enum ItemState {
	Wait = 0,
	Drop = 1
};

enum ItemIcon {
	Bufferly = 10,
	Bird = 11
};

class Item : public InteractiveObj
{
/// Attributes
private:
	static unordered_map<int, LPANI> animations;
	ItemIcon icon;
	ItemKind kind;
	ItemState state;

/// Methods
private:
	void renderIcon(Vector2 viewPos);
	void renderKind(Vector2 viewPos);
	Vector2 handleCollisionWithGround(float dtTime);
	void handleCollisionWithWater(float dtTime);
public:
	/// Commons
	static bool loadResource();
	static void releaseResource();
	Item(ObjKind icon, Vector2 position);
	void update(float dtTime);
	void render(Vector2 camera);
	MOVEBOX getMoveBox(float dtTime);
	/// For game
	void onColliWithMainChar(bool isAtkTruth = false);
};