#ifndef __Stage_h_
#define __Stage_h_


#include "StageManager.h"
#include <OgreCamera.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <MyGUI/MyGUI.h>

/// ��̨�����࣬���𳡾��Ĺ���
/// @author: LiaoNanhao
class Stage
{
public:
	/// ���캯��
	/// @param pSceneManager ������������ָ��
	/// @param pStageManager ��̨��������ָ��
	/// @note �ڹ��캯������ɸ���̨�ĳ�����ص����г�ʼ�����������糡�������ؽ�����Դ�ļ��ص�
	Stage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);

	/// ��������
	virtual ~Stage(void);

	/// �����������߼�
	/// @param timeSinceLastFrame ����һ֡���������ŵ�ʱ��
	/// @note �������ÿһ֡���ã��������ÿһ֡���߼�
	virtual bool run(float timeSinceLastFrame) = 0;

	// ���¼�����Ӧ
	/// ���¼��̴����˺���
	/// @param arg �¼�����Ϣ
	virtual bool onKeyPressed(const OIS::KeyEvent &arg) = 0;

	/// ����ƶ������˺���
	/// @param arg �¼�����Ϣ
	virtual bool onMouseMoved(const OIS::MouseEvent &arg) = 0;

	/// ������괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	virtual bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	/// �ͷ���괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	virtual bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	/// ��ȡ����ͷ
	Ogre::Camera* getCamera();

	/// ��ȡGUI
	MyGUI::Gui* getGUI()
	{
		return mGui;
	}

	/// ������Ч
	/// @note helper function
	static void playSound(const char* fileName, bool loop);
	/// ��������
	static void playMusic(const char* fileName, bool loop);

	static void setSoundFlag(bool isEnable)
	{
		mSoundEnabled = isEnable;
	}

	static bool getSoundFlag()
	{
		return mSoundEnabled;
	}

	static void setMusicFlag(bool isEnable)
	{
		mMusicEnabled = isEnable;
	}

	static bool getMusicFlag()
	{
		return mMusicEnabled;
	}

protected:
	/// ��ת����һ����̨���ڲ�����
	/// @param pNextStage ��һ����̨��ָ��
	void jumpToNextStage(Stage* nextStage);

	/// ����������
	Ogre::SceneManager* mSceneManager;
	/// ���г�����������ָ�룬�Ա�ʵ��״̬ģʽ
	StageManager* mStageManager; 
	/// �����
	Ogre::Camera* mCamera;
	/// MyGUI
	MyGUI::Gui* mGui;
	/// ��Ч���ر�־λ
	static bool mSoundEnabled;
	/// ���ֿ��ر�־λ
	static bool mMusicEnabled;
};


#endif

