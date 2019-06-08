#include <sstream>
#include "DxGraphic.h"
#include "TextureCollection.h"
#include "BoundaryBox.h"
#include "SpacePartitioning.h"
#include "ImmortalObj.h"
#include "TileMap.h"
#include "Scoreboard.h"
#include "Item.h"
#include "BossEnemy.h"
#include "BaseWeapon.h"
#include "MainCharacter.h"
#include "GameWorld.h"

GameWorld* GameWorld::instance = NULL;

bool GameWorld::loadResource()
{
	if (!loadAllTextures()) return false;
	
	if (!scorebar->loadResource()) return false;

	if (!mainChar->loadResource()) return false;
	
	if (!Item::loadResource()) return false;

	if (!BaseWeapon::loadResource()) return false;

	if (!BaseEnemy::loadResource()) return false;

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
	Item::releaseResource();
	BaseWeapon::releaseResource();
	BaseEnemy::releaseResource();
	delete tileMap;
	delete scorebar;
	delete textures;
}

bool GameWorld::initialize()
{
	scorebar = Scoreboard::getInstance();
	tileMap = new TileMap();
	mainChar = MainCharacter::getInstance();

	if (!loadResource()) return false;
	
	if (!newGame()) return false;

	return true;
}

void GameWorld::update(float dtTime)
{
	updateInProcObjsList();
	scorebar->update(dtTime);
	mainChar->update(dtTime);
	for (auto it = inProcObjs.begin(); it != inProcObjs.end(); it++)
		for (unsigned int i = 0; i < it->second.size(); i++)
			it->second[i]->update(dtTime);
	updateCamera();
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
		mainChar->render(camera);

		for (auto it = inProcObjs.begin(); it != inProcObjs.end(); it++)
			for (unsigned int i = 0; i < it->second.size(); i++)
				it->second[i]->render(camera);
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
	
	spacePart.loadFromFile(STAGE_3_1_GRID_FILE, MAP_POS);
	if(!loadGameObjs(Stage::_3_1))
		return false;
	
	mainChar->initialize();

	scorebar->mainHealth = MAX_HEALTH;
	scorebar->enemyHealth = MAX_HEALTH;
	scorebar->timer = 150.f;
	scorebar->score = 0;
	scorebar->items = 0;
	scorebar->players = MAX_PLAYERS;
	scorebar->stage = Stage::_3_1;
	scorebar->curItem = ItemKind::Bonus500;

	return true;
}

void GameWorld::respawn()
{
	tileMap->loadStage(tileMap->stage);

	switch (tileMap->stage)
	{
	case _3_1:
		loadGameObjs(_3_1);
		break;
	case _3_2:
		loadGameObjs(_3_2);
		break;
	case _3_3:
		loadGameObjs(_3_3);
		break;
	default:
		break;
	}

	mainChar->initialize();

	scorebar->mainHealth = MAX_HEALTH;
	scorebar->enemyHealth = MAX_HEALTH;
	scorebar->timer = 150.f;
	scorebar->players--;
}

void GameWorld::nextStage()
{
	switch (tileMap->stage)
	{
	case _3_1:
		tileMap->loadStage(_3_2);
		spacePart.loadFromFile(STAGE_3_2_GRID_FILE, MAP_POS);
		loadGameObjs(_3_2);
		scorebar->stage = _3_2;
		break;
	case _3_2:
		tileMap->loadStage(_3_3);
		spacePart.loadFromFile(STAGE_3_3_GRID_FILE, MAP_POS);
		loadGameObjs(_3_3);
		scorebar->stage = _3_3;
		break;
	default:
		break;
	}
	
	mainChar->initialize();
	mainChar->health = scorebar->mainHealth;

	scorebar->timer = 150.f;
}

bool GameWorld::loadGameObjs(Stage stage)
{
	for (auto iterator : gameObjects)
		delete iterator.second;
	gameObjects.clear();
	inProcObjs.clear();

	STRINGS objsInfoLines;
	switch (stage)
	{
	case _3_1:
		objsInfoLines = readFileText(STAGE_3_1_OBJS_FILE);
		break;
	case _3_2:
		objsInfoLines = readFileText(STAGE_3_2_OBJS_FILE);
		break;
	case _3_3:
		objsInfoLines = readFileText(STAGE_3_3_OBJS_FILE);
		break;
	}
	if (objsInfoLines.size() <= 1)
		return false;
	for (unsigned int i = 1; i < objsInfoLines.size(); i++)
	{
		int id, left_bmp, bottom_bmp, width, height;
		stringstream iss(objsInfoLines[i]);
		iss >> id; iss >> left_bmp; iss >> bottom_bmp; iss >> width; iss >> height;

		Vector2 LeftBot_wP = transformViewToWorld(Vector2(left_bmp, bottom_bmp), MAP_POS);

		LPGAMEOBJ obj = NULL;
		switch (id / OBJ_KIND_WEIGHT)
		{
		case ObjKind::Ground:
		case ObjKind::Stair:
		case ObjKind::Wall:
		case ObjKind::Gate:
		case ObjKind::Water:
			obj = new ImmortalObj(LeftBot_wP, Vector2(width, height));
			this->gameObjects[id] = obj;
			break;
		case ObjKind::Item1:
		case ObjKind::Item2:
			obj = new Item((ObjKind)(id / OBJ_KIND_WEIGHT), LeftBot_wP);
			this->gameObjects[id] = obj;
			break;
		case ObjKind::Boss:
			obj = new BossEnemy(LeftBot_wP, Vector2(width, height));
			this->gameObjects[id] = obj;
			break;
		default:
			break;
		}
	}
	return true;
}

void GameWorld::updateCamera()
{
	Vector2 tempCamera;
	Vector2 clientSize = DxGraphic::getInstance()->clientSize;
	tempCamera.x = mainChar->position.x - clientSize.x / 2;
	if (tempCamera.x < 0)
		camera.x = 0;
	else if (tempCamera.x > tileMap->size.x - clientSize.x)
		camera.x = tileMap->size.x - clientSize.x;
	else
		camera.x = (float)((int)tempCamera.x);
}
