#pragma once
#include "game2dHelper.h"

#define SYS_CONST_GROUP
#define GAME_TITLE L"NINJA GAIDEN NES"
#define IS_FULLSCREEN false
#define SCREEN_W 271
#define SCREEN_H 279
#define MAX_FPS 60

#define MAP_POS Vector2(0, 176)



/// Common
class GameWorld;

/// Immortal Objects
class ImmortalObj;
class TileMap;

/// Constant & Enum
#define TILEMAP_SPRITE_SIZE Vector2(16.f, 16.f)

#define STAGE_3_1_TEXTUREID 0001
#define STAGE_3_2_TEXTUREID 0002
#define STAGE_3_3_TEXTUREID 0003
#define STAGE_3_1_MATRIXFILE "Resource/Maps/TileMap/Stage3-1_matrixmap.txt"
#define STAGE_3_2_MATRIXFILE "Resource/Maps/TileMap/Stage3-2_matrixmap.txt"
#define STAGE_3_3_MATRIXFILE "Resource/Maps/TileMap/Stage3-3_matrixmap.txt"
#define STAGE_3_1_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-1_tileset.bmp"
#define STAGE_3_2_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-2_tileset.bmp"
#define STAGE_3_3_TEXTUREFILE L"Resource/Maps/TileMap/Stage3-3_tileset.bmp"

enum Stage {
	_3_1 = 1,
	_3_2 = 2,
	_3_3 = 3
};

/// Support Functions
bool loadAllTextures();