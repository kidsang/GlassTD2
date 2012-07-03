#ifndef __StagePass1Step0_h_
#define __StagePass1Step0_h_

#include "Step.h"
#include "LevelStage.h"
#include "Maze.h"

/// ��һ�صĲ���׶�
class StagePass1Step0 : public Step
{
public:

	enum State
	{
		NOTHING, WITH_SWAMP/*����*/, WITH_SPIKEWEED/*�ش�*/, WITH_TRAP/*���޼�*/, 
	};

	StagePass1Step0(LevelStage* stagePass1);
	~StagePass1Step0();

	// ʵ�ָ���ĺ���
	void init();
	bool run(float timeSinceLastFrame);
	bool onKeyPressed(const OIS::KeyEvent &arg);
	bool onKeyReleased(const OIS::KeyEvent &arg);
	bool onMouseMoved(const OIS::MouseEvent &arg);
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void setNotify();
	void guiNotifyMousePressSwamp(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMousePressSpikeweed(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMousePressTrap(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMouseReleaseSwamp(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMouseReleaseSpikeweed(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMouseReleaseTrap(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
private:
	/// ���������Ļ�ϵ�����ת���ɳ����е���ά����
	/// @return �ɹ�����true��output��Ϊ��ά���꣬ʧ�ܷ���false
	bool convert(const OIS::MouseEvent& arg, Ogre::Vector3& output);
	
private:
	LevelStage* mStagePass1;
	State mCurrentState;
	Cell* mCurrentCell;
	Ogre::Vector3 mLastPos;
	Ogre::RaySceneQuery* mRaySceneQuery;

	/// ��������X�����־λ
	int mRollX;
	/// ��������Y�����־λ
	int mRollY;
	// debug
	//MyGUI::StaticTextPtr debugText;

	/// ��ʼ��ͷ�����Ƿ��Ѿ�����
	bool mIsIniAniOver;
	/// ��ͷ����λ��
	Ogre::Vector3 mCamEndPos;
	/// ��ͷ��ʼλ��
	Ogre::Vector3 mCamBeginPos;
	/// ��ͷ��ʼ�ӵ�
	Ogre::Vector3 mCamBeginFocus;
	/// ��ͷ�����ӵ�
	Ogre::Vector3 mCamEndFocus;
	/// ��������ʱ��
	float mCamAniTime;
};


#endif