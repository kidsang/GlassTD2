#ifndef CameraStep02Step1Animator_h__
#define CameraStep02Step1Animator_h__

/**
 * 文件：CameraStep02Step1Animator
 * 日期：2012/06/30
 * 作者：kid
 */

#include "Animator.h"
#include "OgreCamera.h"
using namespace Ogre;

/// 从Step0到Step1的镜头移动动画
/// 该类为硬编码，十分丑陋
class CameraStep02Step1Animator : public Animator<Camera>
{
public:
	CameraStep02Step1Animator(float timeInterval)
		: Animator(timeInterval), mCount(40), mFirst(true)
	{

	}

private:
	int mCount;
	bool mFirst;
	Vector3 mPosStep;

	virtual void runImpl( float timeSinceLastFrame, Camera* object ) 
	{
		if (mFirst)
		{
			mFirst = false;
			mPosStep = (Vector3(0, 1000, 1800) - object->getPosition()) / mCount;
		}

		object->setPosition(object->getPosition() + mPosStep);
		object->lookAt(Vector3(0, 0, 0));
		mCount--;
		if (mCount <= 0)
			stop(object);
		//throw std::exception("The method or operation is not implemented.");
		//stop(object);
	}

};

#endif // CameraStep02Step1Animator_h__