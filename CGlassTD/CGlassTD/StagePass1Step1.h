#ifndef __StagePass1Step1_h_
#define __StagePass1Step1_h_

#include "Step.h"
#include "StagePass1.h"
#include "SceneManagerContainer.h"

/// 第一关的打怪阶段
class StagePass1Step1 : public Step
{
public:
	StagePass1Step1(StagePass1* stagePass1);

	// 实现父类的函数
	void init();
	bool run(float timeSinceLastFrame);
	bool onKeyPressed(const OIS::KeyEvent &arg);
	bool onMouseMoved(const OIS::MouseEvent &arg);
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	StagePass1* mStagePass1;
};


#endif