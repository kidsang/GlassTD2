#include "MonsterHurtAnimator.h"

/*void MonsterDead(Monster* monster)
{
	SceneNode* node = monster->getNode();
}*/

MonsterHurtAnimator::MonsterHurtAnimator(float timeInterval)
	: Animator(timeInterval)
{
	//addOnStartCallback(MonsterDead);
	//addOnStopCallback(MonsterDead);
}


MonsterHurtAnimator::~MonsterHurtAnimator(void)
{
}

void MonsterHurtAnimator::runImpl( float timeSinceLastFrame, Monster* object )
{
	// Todo:≤•∑≈ ‹…À∂Øª≠
	//Entity* ent = static_cast<Entity*>(object->getNode()->getAttachedObject(0));
	//ent->
	//ent->get
	//ent->setMaterialName("Glass/White");
}
