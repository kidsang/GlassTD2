#include "MonsterDeadAnimator.h"
#include "MonsterManager.h"

void MonsterDead(Monster* monster)
{
	//SceneNode* node = monster->getNode();
	MonsterManager* mgr = monster->getCreater();
	mgr->destoryMonster(monster);
}

MonsterDeadAnimator::MonsterDeadAnimator(float timeInterval)
	: Animator(timeInterval)
{
	addOnStopCallback(MonsterDead);
}


MonsterDeadAnimator::~MonsterDeadAnimator(void)
{
}
