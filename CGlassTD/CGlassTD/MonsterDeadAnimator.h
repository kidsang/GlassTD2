#ifndef MonsterDeadAnimator_h__
#define MonsterDeadAnimator_h__

#include "Animator.h"
#include "Monster.h"



/// 怪物死亡动画
class MonsterDeadAnimator : public Animator<Monster>
{
public:
	MonsterDeadAnimator(float timeInterval);
	~MonsterDeadAnimator(void);

	virtual void runImpl(float timeSinceLastFrame, Monster* object)
	{
		// 在此调用播放死亡动画

		stop(object);
	}
};

#endif // MonsterDeadAnimator_h__

