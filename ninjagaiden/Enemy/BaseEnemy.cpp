#include <sstream>
#include "TextureCollection.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "BaseEnemy.h"
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

void BaseEnemy::render(Vector2 cam_wP)
{
	Vector2 viewPosition = transformWorldToView(position, cam_wP);
	viewPosition.y += -10;
	 anicollectS[ENEMIES_DYING_ANIS_ID]->getAnimation(0)->render(viewPosition);
}

void BaseEnemy::onCollision()
{
}

void BaseEnemy::releaseResource()
{
	for (auto animations :  anicollectS)
		delete animations.second;
}

void BaseEnemy::updateMoveState(float dtTime)
{
}

void BaseEnemy::updateAttkState(float dtTime)
{
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
