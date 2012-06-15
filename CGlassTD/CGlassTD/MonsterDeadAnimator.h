#ifndef MonsterDeadAnimator_h__
#define MonsterDeadAnimator_h__

#include "Animator.h"
#include "Monster.h"



/// π÷ŒÔÀ¿Õˆ∂Øª≠
class MonsterDeadAnimator : public Animator<Monster>
{
public:
	MonsterDeadAnimator(float timeInterval);
	~MonsterDeadAnimator(void);

	virtual void runImpl(float timeSinceLastFrame, Monster* object);
};

#endif // MonsterDeadAnimator_h__

