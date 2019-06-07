#include "DxGraphic.h"
#include "TextureCollection.h"
#include "ImmortalObj.h"
#include "TileMap.h"
#include "Scoreboard.h"
#include "GameWorld.h"

GameWorld* GameWorld::instance = NULL;

bool GameWorld::loadResource()
{
	if (!loadAllTextures()) return false;

	if (!scorebar->loadResource()) return false;
	
	return true;
}

GameWorld * GameWorld::getInstance()
{
	if (instance == NULL)
		instance = new GameWorld();
	return instance;
}

GameWorld::~GameWorld()
{
	TextureCollection* textures = TextureCollection::getInstance();
	delete tileMap;
	delete scorebar;
	delete textures;
}

bool GameWorld::initialize()
{
	scorebar = Scoreboard::getInstance();
	tileMap = new TileMap();

	if (!loadResource()) return false;
	
	if (!newGame()) return false;

	return true;
}

void GameWorld::update(float dtTime)
{
	scorebar->update(dtTime);

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
		scorebar->render();

		//
		dxGraphic->spriteHandler->End();
		dxGraphic->direct3dDevice->EndScene();
	}
	dxGraphic->direct3dDevice->Present(NULL, NULL, NULL, NULL);
}

bool GameWorld::newGame()
{
	if (!tileMap->loadStage(Stage::_3_1))
		return false;
	
	scorebar->mainHealth = MAX_HEALTH;
	scorebar->enemyHealth = MAX_HEALTH;
	scorebar->timer = 0.f;
	scorebar->score = 0;
	scorebar->items = 0;
	scorebar->players = MAX_PLAYERS;
	scorebar->stage = Stage::_3_1;

	return true;
}
