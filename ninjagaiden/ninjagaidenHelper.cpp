#include "TextureCollection.h"
#include "ninjagaidenHelper.h"

bool loadAllTextures()
{
	TEXTURES* textures = TextureCollection::getInstance();
	bool result;
	result = textures->addTexture(
		STAGE_3_1_TEXTUREID, STAGE_3_1_TEXTUREFILE, Color(255, 0, 255));
	if (!result) return false;

	result = textures->addTexture(
		STAGE_3_2_TEXTUREID, STAGE_3_2_TEXTUREFILE, Color(255, 0, 255));
	if (!result) return false;

	result = textures->addTexture(
		STAGE_3_3_TEXTUREID, STAGE_3_3_TEXTUREFILE, Color(255, 0, 255));
	if (!result) return false;

	result = textures->addTexture(
		SCOREBAR_TEXTUREID, SCOREBAR_TEXTUREFILE, Color(255, 163, 177));
	if (!result) return false;

	result = textures->addTexture(
		MAINCHAR_TEXTUREID, MAINCHAR_TEXTUREFILE, Color(255, 163, 177));
	if (!result) return false;

	result = textures->addTexture(
		ITEMS_TEXTUREID, ITEMS_TEXTUREFILE, Color(255, 163, 177));
	if (!result) return false;

	result = textures->addTexture(
		WEAPONS_TEXTUREID, WEAPONS_TEXTUREFILE, Color(255, 174, 201));
	if (!result) return false;

	result = textures->addTexture(
		ENEMIES_TEXTUREID, ENEMIES_TEXTUREFILE, Color(255, 163, 177));
	if (!result) return false;

	return true;
}
