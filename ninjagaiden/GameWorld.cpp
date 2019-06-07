#include "DxGraphic.h"
#include "TextureCollection.h"
#include "ImmortalObj.h"
#include "TileMap.h"
#include "GameWorld.h"

GameWorld* GameWorld::instance = NULL;

bool GameWorld::loadResource()
{
	if (!loadAllTextures()) return false;

	return true;
}

GameWorld * GameWorld::getInstance()
{
	if (instance == NULL)
		instance = new GameWorld();
	return instance;
}

bool GameWorld::initialize()
{
	if (!loadResource()) return false;

	tileMap = new TileMap();
	if (!tileMap->loadStage(Stage::_3_1))
		return false;

	return true;
}

void GameWorld::update(float dtTiem)
{
	camera.x += 1;
}

void GameWorld::render()
{
	DxGraphic* dxGraphic = DxGraphic::getInstance();
	if (dxGraphic->direct3dDevice->BeginScene())
	{
		//Clear backbuffer with a color
		dxGraphic->direct3dDevice->ColorFill(
			dxGraphic->backBuffer, NULL, Color(0,0,0));

		dxGraphic->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		// Call render function of gameObjects in Game World
		tileMap->render(camera);

		//
		dxGraphic->spriteHandler->End();
		dxGraphic->direct3dDevice->EndScene();
	}
	dxGraphic->direct3dDevice->Present(NULL, NULL, NULL, NULL);
}
