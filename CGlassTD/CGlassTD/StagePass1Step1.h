#ifndef __StagePass1Step1_h_
#define __StagePass1Step1_h_

#include "Step.h"
#include "StagePass1.h"
#include "SceneManagerContainer.h"

class StagePass1Step1 : public Step
{
public:
	StagePass1Step1(StagePass1* stagePass1);

	// 实现父类的函数
	void run(float timeSinceLastFrame);
	void onKeyPressed(const OIS::KeyEvent &arg);
	void onMouseMoved(const OIS::MouseEvent &arg);
	void onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	void onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	StagePass1* mStagePass1;
};


#endif