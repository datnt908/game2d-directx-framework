#include <sstream>
#include "TextureCollection.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "BaseWeapon.h"
#include "GameWorld.h"

unordered_map<int, Sprite*> BaseWeapon::sprites;

bool BaseWeapon::loadResource()
{
	Texture texture = TextureCollection::getInstance()->getTexture(WEAPONS_TEXTUREID);
	if (texture == NULL) return false;

	STRINGS textureInfoLines = readFileText(WEAPONS_TEXTUREINFO_FILE);
	Sprite* sprite;
	int kind, aniID, left, top, right, bottom, centerx, centery;
	if (textureInfoLines.size() <= 1) return false;
	for (int i = 1; i < textureInfoLines.size(); i++)
	{
		stringstream iss(textureInfoLines[i]);
		iss >> kind; iss >> left; iss >> top; iss >> right; iss >> bottom;
		iss >> centerx; iss >> centery;
		RECT tempRect;
		tempRect.left = left;
		tempRect.right = right;
		tempRect.top = top;
		tempRect.bottom = bottom;
		sprite = sprites[kind];
		if (sprite == NULL)
		{
			sprite = new Sprite(texture, tempRect, Vector2(centerx, centery));
			sprites[kind] = sprite;
		}
		else
			return false;
	}
	return true;
}

void BaseWeapon::releaseResource()
{
	for (auto iterator : sprites)
		delete iterator.second;
}

void BaseWeapon::render(Vector2 camera)
{
	Vector2 viewPos = transformWorldToView(position, camera);
	sprites[icon]->setRotate(timeToDie * 360.f);
	sprites[icon]->render(viewPos);
	if (timeToDie <= 0)
		if (isExplosion)
			sprites[Explosion]->render(viewPos);
}

void BaseWeapon::update(float dtTime)
{
	timeToDie -= dtTime;
	if (timeToDie <= -0.1f)
		GameWorld::getInstance()->deleteObject(this);
}

BndBox BaseWeapon::getBndBox(float dtTime)
{
	if(timeToDie <= 0) return BndBox();
	Vector2 center;
	BndBox bb;
	center = sprites[icon]->getCenter();
	bb.size = sprites[icon]->getSize();
	Vector2 positionTransfered = transformViewToWorld(center, Vector2(0, bb.size.y));
	bb.position = position - positionTransfered;
	bb.dtPosition = velocity * dtTime;
	return bb;
}

void BaseWeapon::onCollision(bool isExplosive)
{
	timeToDie = 0;
	if(isExplosive)
		this->isExplosion = true;
}
