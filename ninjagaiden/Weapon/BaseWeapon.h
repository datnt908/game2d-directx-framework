#pragma once
#include "InteractiveObj.h"
#include "ninjagaidenHelper.h"

enum WeaponIcon {
	Weapon1 = 0,
	Weapon3 = 1,
	Weapon6 = 2,
	WeaponB = 3,
	WpBlueDart = 4,
	WpOraDart = 5
};

class BaseWeapon : public InteractiveObj
{
/// Attributes
protected:
	static unordered_map<int,Sprite*> sprites;
public:
	WeaponIcon icon;
	float timeToDie;

/// Methods
public:
	/// Commons
	static bool loadResource();
	static void releaseResource();
	void render(Vector2 camera);
	/// For game
	void onCollision(bool isAtkTruth);
};