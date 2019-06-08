#include "Animation.h"
#include "AnimationCollection.h"
#include "BoundaryBox.h"
#include "CollisionEvent.h"
#include "DuckState.h"
#include "DuckAtkState.h"
#include "MainCharacter.h"
#include "GameWorld.h"

void DuckAtkState::update(float dtTime)
{
	handleCollisionWithBoss(dtTime);
	handleCollisionWithItems(dtTime);
	handleCollisionWithEnemiesAndWeapons(dtTime);
}

void DuckAtkState::handleCollisionWithEnemiesAndWeapons(float dtTime)
{
	
}

void DuckAtkState::handleCollisionWithBoss(float dtTime)
{
	
}

void DuckAtkState::handleKeyInput(bool keyStates[])
{
}
