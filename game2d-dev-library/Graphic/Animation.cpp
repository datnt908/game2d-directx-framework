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
	if (sprite == NULL) return;
	frames.push_back(sprite);
	curFrame = 0;
}

void Animation::subsEndAniEvent(EndAnimationEvent onEndAniFunct)
{
	endAniEvent = onEndAniFunct;
}

void Animation::render(Vector2 viewPos)
{
	if (curFrame == -1) return;
	DWORD now = GetTickCount();
	frames[curFrame]->render(viewPos);
	if (now - lastFrameTime > (DWORD)dtFrameTime)
	{
		curFrame = (curFrame + 1) % frames.size();
		lastFrameTime = now;
		if (endAniEvent != NULL && curFrame == 0)
			endAniEvent();
	}
}

Vector2 Animation::getCurFrameSize()
{
	if (curFrame == -1)
		return Vector2(0.f, 0.f);
	return frames[curFrame]->getSize();
}

Vector2 Animation::getCurFrameCenter()
{
	if (curFrame == -1)
		return Vector2(0.f, 0.f);
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
