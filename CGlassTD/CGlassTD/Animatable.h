#ifndef Animatable_h__
#define Animatable_h__

/**
 * 文件：Animatable
 * 日期：2012/06/17
 * 作者：kid
 */

#include "Animator.h"
#include <list>

/// 可赋予动画之物
/// Animator 的管理类
/// 动画
template <typename T>
class Animatalbe
{
private:
	typedef std::list<Animator<T>*> AnimatorList;
	AnimatorList mAnimatorList;
	AnimatorList mRemoveList;

public:
	/// 运行动画列表
	/// @param timeSinceLastFrame 上一帧(游戏循环)持续的时间
	/// @param object 被动画作用的物体
	/// @note 动画在stop的时候，会被移除并销毁
	void animate(float timeSinceLastFrame, T* object);

	/// 添加一个动画
	void addAnimator(Animator<T>* animator)
	{
		mAnimatorList.push_back(animator);
	}
};

template <typename T>
void Animatalbe<T>::animate( float timeSinceLastFrame, T* object )
{
	for (auto iter = mAnimatorList.begin(); iter != mAnimatorList.end(); ++iter)
		if (!(*iter)->run(timeSinceLastFrame, object))
			mRemoveList.push_back((*iter));

	for (auto iter = mRemoveList.begin(); iter != mRemoveList.end(); ++iter)
	{
		auto iter2 = std::find(mAnimatorList.begin(), mAnimatorList.end(), (*iter));
		delete (*iter2);
		mAnimatorList.erase(iter2);
	}
	mRemoveList.clear();
}

#endif // Animatable_h__
