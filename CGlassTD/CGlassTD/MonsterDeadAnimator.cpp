#include "MonsterDeadAnimator.h"
#include "MonsterManager.h"

void MonsterDead(Monster* monster)
{
	//SceneNode* node = monster->getNode();
	MonsterManager* mgr = monster->getCreater();
	mgr->destoryMonster(monster);
}

MonsterDeadAnimator::MonsterDeadAnimator(float timeInterval)
	: Animator(timeInterval), mDieTime(0.6f)
{
	addOnStopCallback(MonsterDead);
}


MonsterDeadAnimator::~MonsterDeadAnimator(void)
{
}

void MonsterDeadAnimator::runImpl( float timeSinceLastFrame, Monster* object )
{
	// 在此调用播放死亡动画
	object->addTimeToAnimation(timeSinceLastFrame);
	mDieTime -= timeSinceLastFrame;
	if(mDieTime < 0 || mDieTime == 0)
		stop(object);
}
