#ifndef MonsterHurtAnimator_h__
#define MonsterHurtAnimator_h__

/**
 * 文件：MonsterHurtAnimator
 * 日期：2012/06/14
 * 作者：kid
 */

#include "Animator.h"
#include "Monster.h"

/// 怪物受伤后伤血
class MonsterHurtAnimator : public Animator<Monster>
{
public:
	MonsterHurtAnimator(float timeInterval);
	~MonsterHurtAnimator(void);

	virtual void runImpl( float timeSinceLastFrame, Monster* object );

};

#endif // MonsterHurtAnimator_h__

