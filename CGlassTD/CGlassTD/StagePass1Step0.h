#ifndef __StagePass1Step0_h_
#define __StagePass1Step0_h_

#include "Step.h"
#include "StagePass1.h"

/// 第一关的布阵阶段
class StagePass1Step0 : public Step
{
public:
	StagePass1Step0(StagePass1* stagePass1);

	// 实现父类的函数
	void init();
	void run(float timeSinceLastFrame);
	void onKeyPressed(const OIS::KeyEvent &arg);
	void onMouseMoved(const OIS::MouseEvent &arg);
	void onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	void onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	StagePass1* mStagePass1;
};


#endif