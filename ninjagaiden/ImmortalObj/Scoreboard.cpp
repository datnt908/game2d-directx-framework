#include <sstream>
#include "TextureCollection.h"
#include "Sprite.h"
#include "Scoreboard.h"

// Khoảng cách giữa 2 ký tự
#define SCOREBAR_CHAR_DIST Vector2(7, 0)
// Khoảng cách giữa 2 ô máu
#define SCOREBAR_HCELL_DIST Vector2(5, 0)
#define SCOREBAR_SCORE_POS Vector2(64, 17)
#define SCOREBAR_STAGE_POS Vector2(163, 17)
#define SCOREBAR_TIMER_POS Vector2(64, 30)
#define SCOREBAR_NINJA_POS Vector2(163, 30)
#define SCOREBAR_ENEMY_POS Vector2(163, 42)
#define SCOREBAR_ITEMS_POS Vector2(71, 42)
#define SCOREBAR_PLAYERS_POS Vector2(35, 42)
#define SCOREBAR_CUR_ITEM_POS Vector2(101, 39)

Scoreboard* Scoreboard::instance = NULL;

Scoreboard * Scoreboard::getInstance()
{
	if(instance == NULL)
		instance = new Scoreboard();
	return instance;
}

Scoreboard::~Scoreboard()
{
	for (auto sprite : sprites)
		delete sprite;
}

bool Scoreboard::loadResource()
{
	Texture texture = TextureCollection::getInstance()->getTexture(SCOREBAR_TEXTUREID);
	if (texture == NULL) return false;
	STRINGS textureInfoLines = readFileText(SCOREBAR_TEXTURE_INFOFILE);
	if (textureInfoLines.size() <= 1) return false;

	Sprite* sprite;
	for (unsigned int i = 1; i < textureInfoLines.size(); i++)
	{
		int id, left, top, right, bot, centx, centy;
		stringstream iss(textureInfoLines[i]);
		iss >> id; iss >> left; iss >> top; iss >> right; iss >> bot;
		iss >> centx; iss >> centy;
		if (id != sprites.size()) return false;
		RECT tempRect;
		tempRect.left = left;
		tempRect.top = top;
		tempRect.right = right;
		tempRect.bottom = bot;
		sprite = new Sprite(texture, tempRect, Vector2(centx, centy));
		sprites.push_back(sprite);
	}

	return true;
}

void Scoreboard::render()
{
	sprites[15]->render(Vector2(0, 0));
	renderStage();
	renderCurItem();
	renderScore();
	renderTimer();
	renderPlayers();
	renderItems();
	renderHealth();
}

void Scoreboard::update(float dtTime)
{
	timer += dtTime;
}

void Scoreboard::renderStage()
{
	sprites[3]->render(SCOREBAR_STAGE_POS);
	sprites[10]->render(SCOREBAR_STAGE_POS + SCOREBAR_CHAR_DIST);
	switch (stage)
	{
	case _3_1:
		sprites[1]->render(SCOREBAR_STAGE_POS + 2 * SCOREBAR_CHAR_DIST);
		break;
	case _3_2:
		sprites[2]->render(SCOREBAR_STAGE_POS + 2 * SCOREBAR_CHAR_DIST);
		break;
	case _3_3:
		sprites[3]->render(SCOREBAR_STAGE_POS + 2 * SCOREBAR_CHAR_DIST);
		break;
	}
}

void Scoreboard::renderCurItem()
{
	switch (curItem)
	{
	case BlueDart:
		sprites[13]->render(SCOREBAR_CUR_ITEM_POS);
		break;
	case OrangeDart:
		sprites[14]->render(SCOREBAR_CUR_ITEM_POS);
		break;
	default:
		break;
	}
}

void Scoreboard::renderScore()
{
	char content[7];
	sprintf_s(content, "%06d", score);
	for (unsigned int i = 0; i < 6; i++)
		sprites[content[i] - 48]->render(SCOREBAR_SCORE_POS + i * SCOREBAR_CHAR_DIST);
}

void Scoreboard::renderTimer()
{
	char content[4];
	sprintf_s(content, "%03d", (int)timer);
	for (unsigned int i = 0; i < 3; i++)
		sprites[content[i] - 48]->render(SCOREBAR_TIMER_POS + i * SCOREBAR_CHAR_DIST);
}

void Scoreboard::renderPlayers()
{
	char content[3];
	sprintf_s(content, "%02d", players);
	for (unsigned int i = 0; i < 2; i++)
		sprites[content[i] - 48]->render(SCOREBAR_PLAYERS_POS + i * SCOREBAR_CHAR_DIST);
}

void Scoreboard::renderItems()
{
	char content[3];
	sprintf_s(content, "%02d", items);
	for (unsigned int i = 0; i < 2; i++)
		sprites[content[i] - 48]->render(SCOREBAR_ITEMS_POS + i * SCOREBAR_CHAR_DIST);
}

void Scoreboard::renderHealth()
{
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		if(i < enemyHealth)
			sprites[12]->render(SCOREBAR_ENEMY_POS + i * SCOREBAR_HCELL_DIST);
		else
			sprites[11]->render(SCOREBAR_ENEMY_POS + i * SCOREBAR_HCELL_DIST);

		if(i < mainHealth)
			sprites[12]->render(SCOREBAR_NINJA_POS + i * SCOREBAR_HCELL_DIST);
		else
			sprites[11]->render(SCOREBAR_NINJA_POS + i * SCOREBAR_HCELL_DIST);
	}
}
