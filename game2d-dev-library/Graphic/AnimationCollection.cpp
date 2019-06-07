#include "Animation.h"
#include "AnimationCollection.h"

AnimationCollection::~AnimationCollection()
{
	for (auto ani : animationStorage)
		delete ani.second;
}

bool AnimationCollection::addAnimation(int id, LPANI animation)
{
	if (animation != NULL)
		if (animationStorage.find(id) == animationStorage.end())
		{
			animationStorage[id] = animation;
			return true;
		}
	return false;
}

LPANI AnimationCollection::getAnimation(int id)
{
	if (animationStorage.find(id) != animationStorage.end())
		return animationStorage[id];
	return NULL;
}
