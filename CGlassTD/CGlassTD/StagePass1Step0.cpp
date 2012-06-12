#include "StagePass1Step0.h"


StagePass1Step0::StagePass1Step0(StagePass1* stagePass1)
	: mStagePass1(stagePass1)
{
}

void StagePass1Step0::init()
{
	/// 改变镜头视角
	mStagePass1->getCamera()->setPosition(Vector3(0, 2000, 1000));
	mStagePass1->getCamera()->setDirection(-mStagePass1->getCamera()->getPosition());
}

void StagePass1Step0::run(float timeSinceLastFrame)
{
}

void StagePass1Step0::onKeyPressed(const OIS::KeyEvent& arg)
{
	// 按 G 结束布局阶段，开始打怪阶段
	if (arg.key == OIS::KC_G)
	{
		mStagePass1->jumpToStep(1);
	}
}

void StagePass1Step0::onMouseMoved(const OIS::MouseEvent& arg)
{
}

void StagePass1Step0::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}

void StagePass1Step0::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}