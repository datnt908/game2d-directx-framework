#pragma once
#include "BaseTileMap.h"
#include "ninjagaidenHelper.h"

class TileMap : public BaseTileMap
{
/// Attributes
public:
	Stage stage;

/// Methodsx
public:
	bool loadResource();
	void update(float dtTime) {}
	bool loadStage(Stage stage);
};