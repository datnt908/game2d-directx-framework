#pragma once
#include "game2dHelper.h"

class Animation
{
/// Attributes
private:
	DWORD lastFrameTime;
	int dtFrameTime;
	int curFrame;
	SPRITES frames;
	EndAnimationEvent endAniEvent;

/// Methods
public: 
	Animation(int dtFrameTime = 100);
	~Animation();
	void addFrame(Sprite* sprite);
	void subsEndAniEvent(EndAnimationEvent onEndAniFunct);
	void render(Vector2 viewPos);
	Vector2 getCurFrameSize();
	Vector2 getCurFrameCenter();
	void setRotate(float degrees);
	void setScale(Vector2 scaleRatio);
};