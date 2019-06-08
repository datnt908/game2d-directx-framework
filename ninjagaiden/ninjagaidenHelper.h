#pragma once
#include "game2dHelper.h"

#define SYS_CONST_GROUP
#define GAME_TITLE L"NINJA GAIDEN NES"
#define IS_FULLSCREEN false
#define SCREEN_W 271
#define SCREEN_H 279
#define MAX_FPS 60


/// Common
class GameWorld;
class MainCharacter;

/// Immortal Objects
class ImmortalObj;
class TileMap;
class Scoreboard;

/// Weapons
class BaseWeapon;
class StraightWeapon;
class BoomerangWeapon;
class ParapolWeapon;

/// Enemies
class BaseEnemy;

/// Item
class Item;

/// Constant & Enum

#define MAP_POS Vector2(0, 176)
#define TILEMAP_SPRITE_SIZE Vector2(16.f, 16.f)
#define MAX_HEALTH 15
#define MAX_PLAYERS 2

#define FALL_SPEED 450

#define STAGE_3_1_TEXTUREID 0x001
#define STAGE_3_2_TEXTUREID 0x002
#define STAGE_3_3_TEXTUREID 0x003
#define STAGE_3_1_MATRIXFILE "Resource/Maps/TileMap/Stage3-1_matrixmap.txt"
#define STAGE_3_2_MATRIXFILE "Resource/Maps/TileMap/Stage3-2_matrixmap.txt"
#define STAGE_3_3_MATRIXFILE "Resource/Maps/TileMap/Stage3-3_matrixmap.txt"
#define STAGE_3_1_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-1_tileset.bmp"
#define STAGE_3_2_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-2_tileset.bmp"
#define STAGE_3_3_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-3_tileset.bmp"
#define STAGE_3_1_GRID_FILE "Resource/Maps/SpacePartitioning/Stage3_1_Grid.txt"
#define STAGE_3_2_GRID_FILE "Resource/Maps/SpacePartitioning/Stage3_2_Grid.txt"
#define STAGE_3_3_GRID_FILE "Resource/Maps/SpacePartitioning/Stage3_3_Grid.txt"
#define STAGE_3_1_OBJS_FILE "Resource/Maps/SpacePartitioning/Stage3_1_ObjectsList.txt"
#define STAGE_3_2_OBJS_FILE "Resource/Maps/SpacePartitioning/Stage3_2_ObjectsList.txt"
#define STAGE_3_3_OBJS_FILE "Resource/Maps/SpacePartitioning/Stage3_3_ObjectsList.txt"

#define SCOREBAR_TEXTUREID 0x004
#define SCOREBAR_TEXTUREFILE L"Resource/ScoreBoard/scoreboard.bmp"
#define SCOREBAR_TEXTURE_INFOFILE "Resource/ScoreBoard/scoreboard.txt"

#define MAINCHAR_TEXTUREID 0x005
#define MAINCHAR_TEXTUREFILE L"Resource/MainChar/MainCharacter.bmp"
#define MAINCHAR_TEXTUREINFO_FILE "Resource/MainChar/MainCharacter.txt"

#define ITEMS_TEXTUREID 0x006
#define ITEMS_TEXTUREFILE L"Resource/Item/Items.bmp"
#define ITEMS_TEXTUREINFO_FILE "Resource/Item/Items.txt"

#define WEAPONS_TEXTUREID 0x007
#define WEAPONS_TEXTUREFILE L"Resource/Weapon/Weapons.bmp"
#define WEAPONS_TEXTUREINFO_FILE "Resource/Weapon/Weapons.txt"

#define ENEMIES_TEXTUREID 0x008
#define ENEMIES_TEXTUREFILE L"Resource/Enemies/Enemies.bmp"
#define ENEMIES_TEXTUREINFO_FILE "Resource/Enemies/Enemies.txt"

enum Stage {
	_3_1 = 1,
	_3_2 = 2,
	_3_3 = 3
};

enum ItemKind {
	Bonus500 = 0,
	Bonus1000 = 1,
	HealthRes = 2,
	AddItems5 = 3,
	AddItems10 = 4,
	BlueDart = 5,
	OrangeDart = 6
};

enum ObjKind {
	Ground = 0,
	Stair = 1,
	Enemy1 = 2,
	Enemy2 = 3,
	Enemy3 = 4,
	Enemy4 = 5,
	Enemy5 = 6,
	Enemy6 = 7,
	Enemy7 = 8,
	Boss = 9,
	Item1 = 10,
	Item2 = 11,
	Wall = 12,
	Gate = 13,
	Water = 14,
	StraightWp = 15,
	BoomerangWp = 16,
	ParabolWp = 17
};



/// Support Functions
bool loadAllTextures();