#pragma once
#include "game2dHelper.h"

class AnimationCollection
{
/// Attributes
private:
	unordered_map<int, LPANI> animationStorage;

/// Methods
public:
	~AnimationCollection();
	bool addAnimation(int id, LPANI animation);
	LPANI getAnimation(int id);
};