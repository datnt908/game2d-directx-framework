#pragma once
#include "ninjagaidenHelper.h"

class Scoreboard
{
/// Attributes
private:
	static Scoreboard* instance;
	SPRITES sprites;

public:
	Stage stage;
	ItemKind curItem;
	int score;
	float timer;
	int players;
	int items;
	int mainHealth;
	int enemyHealth;
	
/// Methods
private:
	void renderStage();
	void renderCurItem();
	void renderScore();
	void renderTimer();
	void renderPlayers();
	void renderItems();
	void renderHealth();
public:
	static Scoreboard* getInstance();
	~Scoreboard();
	bool loadResource();
	void render();
	void update(float dtTime);
};