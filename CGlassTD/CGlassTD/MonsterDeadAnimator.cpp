#include "MonsterDeadAnimator.h"

void MonsterDead(Monster* monster)
{
	SceneNode* node = monster->getNode();
}

MonsterDeadAnimator::MonsterDeadAnimator(float timeInterval)
	: Animator(timeInterval)
{
	addOnStopCallback(MonsterDead);
}


MonsterDeadAnimator::~MonsterDeadAnimator(void)
{
}
