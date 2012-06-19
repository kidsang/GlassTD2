#ifndef Animatable_h__
#define Animatable_h__

/**
 * �ļ���Animatable
 * ���ڣ�2012/06/17
 * ���ߣ�kid
 */

#include "Animator.h"
#include <list>

/// �ɸ��趯��֮��
/// Animator �Ĺ�����
/// ����
template <typename T>
class Animatalbe
{
private:
	typedef std::list<Animator<T>*> AnimatorList;
	AnimatorList mAnimatorList;
	AnimatorList mRemoveList;

public:
	/// ���ж����б�
	/// @param timeSinceLastFrame ��һ֡(��Ϸѭ��)������ʱ��
	/// @param object ���������õ�����
	/// @note ������stop��ʱ�򣬻ᱻ�Ƴ�������
	void animate(float timeSinceLastFrame, T* object);

	/// ���һ������
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
