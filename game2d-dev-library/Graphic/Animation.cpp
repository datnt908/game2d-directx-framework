#include "Sprite.h"
#include "Animation.h"

Animation::Animation(int dtFrameTime)
{
	this->dtFrameTime = dtFrameTime;
	this->curFrame = -1;
	this->lastFrameTime = -1;
	endAniEvent = NULL;
}

Animation::~Animation()
{
	for (auto sprite : frames)
		delete sprite;
}

void Animation::addFrame(Sprite * sprite)
{
	if (sprite != NULL)
		frames.push_back(sprite);
}

void Animation::subsEndAniEvent(EndAnimationEvent onEndAniFunct)
{
	endAniEvent = onEndAniFunct;
}

Vector2 Animation::getCurFrameSize()
{
	if (curFrame == -1)
		return Vector2(0, 0);
	return frames[curFrame]->getSize();
}

Vector2 Animation::getCurFrameCenter()
{
	if (curFrame == -1)
		return Vector2(0, 0);
	return frames[curFrame]->getCenter();
}

void Animation::setRotate(float degrees)
{
	for (auto sprite : frames)
		sprite->setRotate(degrees);
}

void Animation::setScale(Vector2 scaleRatio)
{
	for (auto sprite : frames)
		sprite->setScale(scaleRatio);
}
