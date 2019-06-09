#include <sstream>
#include "DxSound.h"
#include "TextureCollection.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "collisionHelper.h"
#include "BaseEnemy.h"
#include "Scoreboard.h"
#include "GameWorld.h"

unordered_map<int, LPANIS> BaseEnemy:: anicollectS;

void BaseEnemy::update(float dtTime)
{
	switch (state)
	{
	case MOVE:
		updateMoveState(dtTime);
		break;
	case ATTACK:
		updateAttkState(dtTime);
		break;
	case DEAD:
		updateDeadState(dtTime);
		break;
	}
}

void BaseEnemy::render(Vector2 camera)
{
	Vector2 viewPos = transformWorldToView(position, camera);
	switch (state)
	{
	case MOVE:
		anicollectS[enemyKind]->getAnimation(state)->setScale(Vector2(direction, 1));
		anicollectS[enemyKind]->getAnimation(state)->render(viewPos);
		break;
	case ATTACK:
		anicollectS[enemyKind]->getAnimation(state)->setScale(Vector2(direction, 1));
		anicollectS[enemyKind]->getAnimation(state)->render(viewPos);
		break;
	case DEAD:
		viewPos.y += -10;
		anicollectS[ENEMIES_DYING_ANIS_ID]->getAnimation(0)->render(viewPos);
		break;
	}
}

void BaseEnemy::onCollision()
{
	state = EnemyState::DEAD;
	DxSound::getInstance()->playSound(ENEMY_DIE_SOUND_ID);
	Scoreboard::getInstance()->score += 250;
}

MOVEBOX BaseEnemy::getMoveBox(float dtTime)
{
	if (state == EnemyState::DEAD) return MOVEBOX();
	MOVEBOX bb; Vector2 center;
	center = anicollectS[enemyKind]->getAnimation(state)->getCurFrameCenter();
	bb.size = anicollectS[enemyKind]->getAnimation(state)->getCurFrameSize();;
	if (direction == -1)
		center.x = bb.size.x - center.x;
	Vector2 positionTransfered = transformViewToWorld(center, Vector2(0, bb.size.y));
	bb.position = position - positionTransfered;
	bb.dtPosition = velocity * dtTime;
	return bb;
}

void BaseEnemy::releaseResource()
{
	for (auto animations :  anicollectS)
		delete animations.second;
}

BaseEnemy::BaseEnemy(ObjKind kind, Vector2 position)
{
	enemyKind = kind;
	this->position = position;
	this->velocity = Vector2(0, 0);
	state = EnemyState::MOVE;
	timeToDie = ENEMIES_TIME_TO_DIE;
}

void BaseEnemy::updateDeadState(float dtTime)
{
	timeToDie -= dtTime;
	if (timeToDie <= 0)
		GameWorld::getInstance()->deleteObject(this);
}

bool BaseEnemy::loadResource()
{
	LPDIRECT3DTEXTURE9 texture = TextureCollection::getInstance()->getTexture(ENEMIES_TEXTUREID);
	if (texture == NULL)
		return false;
	
	vector<string> textureInfoLines = readFileText(ENEMIES_TEXTUREINFO_FILE);
	int kind, aniID, left, top, right, bottom, centerx, centery;
	LPANIS animations;
	LPANI animation;
	for (int i = 1; i < textureInfoLines.size(); i++)
	{
		stringstream iss(textureInfoLines[i]);
		iss >> kind; iss >> aniID; iss >> left; iss >> top; iss >> right; iss >> bottom;
		iss >> centerx; iss >> centery;
		RECT tempRect;
		tempRect.left = left;
		tempRect.top = top;
		tempRect.right = right;
		tempRect.bottom = bottom;
		animations =  anicollectS[kind];
		if (animations == NULL)
		{
			animations = new AnimationCollection();
			 anicollectS[kind] = animations;
		}
		animation = animations->getAnimation(aniID);
		if (animation == NULL)
		{
			animation = new Animation(150);
			animations->addAnimation(aniID, animation);
		}
		animation->addFrame(new Sprite(texture, tempRect, Vector2(centerx, centery)));
	}
	return true;
}
