#include <sstream>
#include "DxSound.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "TextureCollection.h"
#include "Sprite.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "Scoreboard.h"
#include "Item.h"
#include "MainCharacter.h"
#include "GameWorld.h"

unordered_map<int, LPANI> Item::animations;

void Item::renderIcon(Vector2 viewPos)
{
	if (animations[icon] != NULL)
		animations[icon]->render(viewPos);
}

void Item::renderKind(Vector2 viewPos)
{
	if (animations[kind] != NULL)
		animations[kind]->render(viewPos);
}

Vector2 Item::handleCollisionWithGround(float dtTime)
{
	velocity.y += -FALL_SPEED * dtTime;
	Vector2 displayment = dtTime * velocity;

	COLLIEVENTS coEvents;
	calculateColli(
		GameWorld::getInstance()->getInProcObjs(ObjKind::Ground),
		dtTime, coEvents
	);

	for (auto coEvent : coEvents)
		if (coEvent->normal.y == 1)
		{
			displayment.y *= coEvent->colliTime;
			velocity.y = 0;
		}

	return displayment;
}

void Item::handleCollisionWithWater(float dtTime)
{
	COLLIEVENTS coEvents;
	calculateColli(
		GameWorld::getInstance()->getInProcObjs(ObjKind::Water),
		dtTime, coEvents
	);
	if (coEvents.size())
		if(coEvents[0]->normal = Vector2(0, 0))
			GameWorld::getInstance()->deleteObject(this);
}

bool Item::loadResource()
{
	Texture texture = TextureCollection::getInstance()->getTexture(ITEMS_TEXTUREID);
	if (texture == NULL) return false;

	STRINGS textureInfoLines = readFileText(ITEMS_TEXTUREINFO_FILE);
	LPANI animation;
	int kind, aniID, left, top, right, bottom, centerx, centery;
	if (textureInfoLines.size() <= 1) return false;
	for (int i = 1; i < textureInfoLines.size(); i++)
	{
		stringstream iss(textureInfoLines[i]);
		iss >> kind; iss >> aniID; iss >> left; iss >> top; iss >> right; iss >> bottom;
		iss >> centerx; iss >> centery;

		animation = animations[kind];
		if (animation == NULL)
		{
			animation = new Animation(150);
			animations[kind] = animation;
		}
		RECT tempRect;
		tempRect.left = left;
		tempRect.right = right;
		tempRect.top = top;
		tempRect.bottom = bottom;
		animation->addFrame(new Sprite(texture, tempRect, Vector2(centerx, centery)));
	}
	return true;
}

void Item::releaseResource()
{
	for (auto iterator : animations)
		delete iterator.second;
}

Item::Item(ObjKind icon, Vector2 position)
{
	switch (icon)
	{
	case Item1:
		this->icon = ItemIcon::Bufferly;
		break;
	case Item2:
		this->icon = ItemIcon::Bird;
		break;
	default:
		break;
	}
	this->position = position;
	this->velocity = Vector2(0, 0);
	this->state = ItemState::Wait;
	this->kind = (ItemKind)(rand() % 7);
}

void Item::update(float dtTime)
{
	switch (state)
	{
	case Drop:
		position.y += handleCollisionWithGround(dtTime).y;
		handleCollisionWithWater(dtTime);
		break;
	default:
		break;
	}
}

void Item::render(Vector2 camera)
{
	Vector2 viewPos = transformWorldToView(position, camera);
	switch (state)
	{
	case Wait:
		renderIcon(viewPos);
		break;
	case Drop:
		renderKind(viewPos);
		break;
	}
}

BndBox Item::getBndBox(float dtTime)
{
	BndBox bb;
	Vector2 center;
	switch (state)
	{
	case Wait:
		if (animations[icon] != NULL)
		{
			center = animations[icon]->getCurFrameCenter();
			bb.size = animations[icon]->getCurFrameSize();
		}
		break;
	case Drop:
		if (animations[kind] != NULL)
		{
			center = animations[kind]->getCurFrameCenter();
			bb.size = animations[kind]->getCurFrameSize();
		}
		break;
	}
	Vector2 positionTransfered = transformViewToWorld(center, Vector2(0, bb.size.y));
	bb.position = position - positionTransfered;
	bb.dtPosition = velocity * dtTime;
	return bb;
}

// Nếu truyền vào true tức item được đánh để rơi ra
void Item::onColliWithMainChar(bool isAtkTruth)
{
	Scoreboard* scoreBar = Scoreboard::getInstance();
	switch (state)
	{
	case Wait:
		if (isAtkTruth)
		{
			state = Drop;
			velocity.y = 100;
		}
		break;
	case Drop:
		if (isAtkTruth) return;
 		switch (kind)
		{
		case Bonus500:
			scoreBar->score += 500;
			break;
		case Bonus1000:
			scoreBar->score += 1000;
			break;
		case HealthRes:
			scoreBar->mainHealth = MAX_HEALTH;
			MainCharacter::getInstance()->health = MAX_HEALTH;
			break;
		case AddItems5:
			scoreBar->items += 5;
			break;
		case AddItems10:
			scoreBar->items += 10;
			break;
		case BlueDart:
			scoreBar->curItem = ItemKind::BlueDart;
			break;
		case OrangeDart:
			scoreBar->curItem = ItemKind::OrangeDart;
			break;
		default:
			break;
		}
		GameWorld::getInstance()->deleteObject(this);
		DxSound::getInstance()->playSound(ITEM_PICKED_SOUND_ID);
		break;
	default:
		break;
	}
}
