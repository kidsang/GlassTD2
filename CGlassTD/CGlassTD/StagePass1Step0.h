#ifndef __StagePass1Step0_h_
#define __StagePass1Step0_h_

#include "Step.h"
#include "StagePass1.h"
#include "Maze.h"

/// ��һ�صĲ���׶�
class StagePass1Step0 : public Step
{
public:

	enum State
	{
		NOTHING, WITH_SWAMP/*����*/, WITH_SPIKEWEED/*�ش�*/, WITH_TRAP/*���޼�*/, 
	};

	StagePass1Step0(StagePass1* stagePass1);
	~StagePass1Step0();

	// ʵ�ָ���ĺ���
	void init();
	bool run(float timeSinceLastFrame);
	bool onKeyPressed(const OIS::KeyEvent &arg);
	bool onMouseMoved(const OIS::MouseEvent &arg);
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	/// ���������Ļ�ϵ�����ת���ɳ����е���ά����
	/// @return �ɹ�����true��output��Ϊ��ά���꣬ʧ�ܷ���false
	bool convert(const OIS::MouseEvent& arg, Ogre::Vector3& output);
	
private:
	StagePass1* mStagePass1;
	State mCurrentState;
	Cell* mCurrentCell;
	Ogre::Vector3 mLastPos;
	Ogre::RaySceneQuery* mRaySceneQuery;

	// debug
	MyGUI::StaticTextPtr debugText;
};


#endif