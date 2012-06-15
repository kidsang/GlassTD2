#ifndef MonsterDeadAnimator_h__
#define MonsterDeadAnimator_h__

#include "Animator.h"
#include "Monster.h"



/// ������������
class MonsterDeadAnimator : public Animator<Monster>
{
public:
	MonsterDeadAnimator(float timeInterval);
	~MonsterDeadAnimator(void);

	virtual void runImpl(float timeSinceLastFrame, Monster* object)
	{
		// �ڴ˵��ò�����������

		stop(object);
	}
};

#endif // MonsterDeadAnimator_h__

