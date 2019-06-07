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

/// Immortal Objects
class ImmortalObj;
class TileMap;
class Scoreboard;

/// Constant & Enum

#define MAP_POS Vector2(0, 176)
#define TILEMAP_SPRITE_SIZE Vector2(16.f, 16.f)
#define MAX_HEALTH 15
#define MAX_PLAYERS 2

#define STAGE_3_1_TEXTUREID 0001
#define STAGE_3_2_TEXTUREID 0002
#define STAGE_3_3_TEXTUREID 0003
#define STAGE_3_1_MATRIXFILE "Resource/Maps/TileMap/Stage3-1_matrixmap.txt"
#define STAGE_3_2_MATRIXFILE "Resource/Maps/TileMap/Stage3-2_matrixmap.txt"
#define STAGE_3_3_MATRIXFILE "Resource/Maps/TileMap/Stage3-3_matrixmap.txt"
#define STAGE_3_1_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-1_tileset.bmp"
#define STAGE_3_2_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-2_tileset.bmp"
#define STAGE_3_3_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-3_tileset.bmp"

#define SCOREBAR_TEXTUREID 0004
#define SCOREBAR_TEXTUREFILE L"Resource/ScoreBoard/scoreboard.bmp"
#define SCOREBAR_TEXTURE_INFOFILE "Resource/ScoreBoard/scoreboard.txt"

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

/// Support Functions
bool loadAllTextures();