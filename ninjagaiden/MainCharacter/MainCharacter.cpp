#include <sstream>
#include "TextureCollection.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "collisionHelper.h"

#include "BaseState.h"
#include "JumpState.h"
#include "StraightWeapon.h"
#include "BoomerangWeapon.h"
#include "MainCharacter.h"
#include "Scoreboard.h"
#include "GameWorld.h"

MainCharacter* MainCharacter::instance = NULL;

void MainCharacter::update(float dtTime)
{
	updateWeapon(dtTime);
	state->update(dtTime);
}

bool MainCharacter::loadResource()
{
	Texture texture = TextureCollection::getInstance()->getTexture(MAINCHAR_TEXTUREID);
	if (texture == NULL) return false;

	vector<string> textureInfoLines = readFileText(MAINCHAR_TEXTUREINFO_FILE);
	if (textureInfoLines.size() <= 1) return false;

	animations = new AnimationCollection();
	LPANI animation;
	for (unsigned int i = 1; i < textureInfoLines.size(); i++)
	{
		int aniID, left, top, right, bot, centerX, centerY;
		std::stringstream iss(textureInfoLines[i]);
		iss >> aniID; iss >> left; iss >> top; iss >> right; iss >> bot; iss >> centerX; iss >> centerY;

		animation = animations->getAnimation(aniID);
		if (animation == NULL)
		{
			animation = new Animation(100);
			animations->addAnimation(aniID, animation);
			if (aniID == MainCharacterState::DuckAtk 
				|| aniID == MainCharacterState::StandAtk
				|| aniID == MainCharacterState::SpawnDart)
				animation->subsEndAniEvent(OnEndAttackAnimation);
		}

		RECT tempRect;
		tempRect.left = left;
		tempRect.top = top;
		tempRect.right = right;
		tempRect.bottom = bot;

		animation->addFrame(new Sprite(texture, tempRect, Vector2(centerX, centerY)));
	}
	return true;
}

MOVEBOX MainCharacter::getMoveBox(float dtTime)
{
	return state->getMoveBox(dtTime);
}

void MainCharacter::render(Vector2 camera)
{
	Vector2 viewPos = transformWorldToView(position, camera);
	state->render(viewPos);
	if(weapon != NULL)
		weapon->render(camera);
}

void MainCharacter::handleKeyInput(bool keyStates[])
{
	state->handleKeyInput(keyStates);
}

MainCharacter* MainCharacter::getInstance()
{
	if (instance == NULL)
		instance = new MainCharacter();
	return instance;
}

void MainCharacter::initialize()
{
	setDirection(1);
	health = MAX_HEALTH;
	position = Vector2(50, 50);
	velocity = Vector2(0, 0);
	state = &BaseState::jumping;
}

MainCharacter::~MainCharacter()
{
	delete animations;
}

COLLIEVENTS MainCharacter::getColliWithObjsByKind(int objKind, float dtTime)
{
	MOVEBOX bbMain = this->getMoveBox(dtTime);
	GameWorld* gameWorld = GameWorld::getInstance();
	COLLIEVENTS colliEvents;
		calculateColli(gameWorld->getInProcObjs(objKind), dtTime, colliEvents);
	return colliEvents;
}

void MainCharacter::updateWeapon(float dtTime)
{
	if (weapon != NULL)
	{
		weapon->updateMainCharWeapon(dtTime);
		if (weapon->timeToDie <= 0)
		{
			delete weapon;
			weapon = NULL;
		}
	}
}

void MainCharacter::setDirection(int direction)
{
	if (direction == this->direction) return;
	animations->getAnimation(MainCharacterState::Idle)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::Move)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::Jump)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::Duck)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::Climb)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::DuckAtk)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::StandAtk)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::Immortal)->setScale(Vector2(direction, 1));
	animations->getAnimation(MainCharacterState::SpawnDart)->setScale(Vector2(direction, 1));
	this->direction = direction;
}