#ifndef MonsterHurtAnimator_h__
#define MonsterHurtAnimator_h__

/**
 * �ļ���MonsterHurtAnimator
 * ���ڣ�2012/06/14
 * ���ߣ�kid
 */

#include "Animator.h"
#include "Monster.h"

/// �������˺���Ѫ
class MonsterHurtAnimator : public Animator<Monster>
{
public:
	MonsterHurtAnimator(float timeInterval);
	~MonsterHurtAnimator(void);

	virtual void runImpl( float timeSinceLastFrame, Monster* object );

};

#endif // MonsterHurtAnimator_h__

