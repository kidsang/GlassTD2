#ifndef __LevelStage_h_
#define __LevelStage_h_

#include <vector>
using std::vector;
#include "Stage.h"
#include "Step.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"
#include "Animator.h"
#include "Money.h"

class LevelStage : public Stage
{
private:
	int mLevel;
	String* mWallType;
	bool mKeyboardControl;
	bool quitFlag;
public:
	/// ���캯��
	LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui, int level);

	/// ��������
	virtual ~LevelStage();

	/// ��ȡ��ǰ�ؿ�
	int getLevel();

	bool getQuitFlag()
	{
		return quitFlag;
	}
	bool getKeyboardController();
	/// ������i������
	void jumpToStep(Step* step);

	/// �����������߼�
	/// @param timeSinceLastFrame ����һ֡���������ŵ�ʱ��
	/// @note �������ÿһ֡���ã��������ÿһ֡���߼�
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool run(float timeSinceLastFrame);

	// ���¼�����Ӧ
	/// ���¼��̴����˺���
	/// @param arg �¼�����Ϣ
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onKeyPressed(const OIS::KeyEvent &arg);

	/// ����ƶ������˺���
	/// @param arg �¼�����Ϣ
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onMouseMoved(const OIS::MouseEvent &arg);

	/// ������괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/// �ͷ���괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/// ���һ�����������
	void addCameraAnimator(Animator<Ogre::Camera>* ani)
	{
		mCameraAnimatorList.push_back(ani);
	}
	///�������������UI����
	void createGUI0();

	///���������ڵ���UI����
	void createGUI1();

	///�����ڵ���
	void updateCount();

	///�����ڵ�ͼƬ
	void updateImage();

	///����ת��ʱ�л�UI
	void change0to1();
	void change1to0();

	///
	// Get/Set
public:
	bool isRunning()
	{
		return mIsRunning;
	}

	bool isEnd()
	{
		return mIsEnd;
	}

	void setEnd(bool isEnd)
	{
		mIsEnd = isEnd;
	}

	void setRunning(bool isRunning)
	{
		mIsRunning = isRunning;
	}

	Cannon* getCannon()
	{
		return mCannon;
	}

	Maze* getMaze()
	{
		return mMaze;
	}

	UFO* getUFO()
	{
		return mUFO;
	}

	MonsterManager* getMonsterManager()
	{
		return mMonsterManager;
	}

	BulletManager* getBulletManager()
	{
		return mBulletManager;
	}

	const Vector3& getGravity()
	{
		return mGravity;
	}

	void setGravity(const Vector3& gravity)
	{
		mGravity = gravity;
	}

	// helper functions
	MyGUI::VectorWidgetPtr getLevelStageLayout()
	{
		return levelStageLayout;
	}


protected:
	/// ��ʼ������
	/// @param cannonDefine ���ڶ���xml�ļ�
	/// @param bulletDefine �ڵ�����xml�ļ�
	void initializeCannon(const std::string& cannonDefine, const std::string& bulletDefine);

	/// ��ʼ���Թ�
	/// @param mazeDefine �Թ�����xml�ļ�
	/// @param cellDefine ǽ����xml�ļ�
	void initializeMaze(const std::string& mazeDefine, const std::string& cellDefine);

	/// ��ʼ��UFO
	/// @param ufoDefine UFO����xml�ļ�
	void initializeUFO(const std::string& ufoDefine);

	
protected:
	/// ��ǰ�ķֳ���
	Step* mCurrentStep;
	/// ��
	Cannon* mCannon;
	/// �Թ�
	Maze* mMaze;
	/// UFO
	UFO* mUFO;
	/// �������й�����
	MonsterManager* mMonsterManager;

	/// �ڵ�������
	BulletManager* mBulletManager;
	/// ����������б�
	std::deque<Animator<Ogre::Camera>*> mCameraAnimatorList;

	/// ��������
	Vector3 mGravity;
	/// �����Ƿ�������
	bool mIsRunning;
	
	// ��Ϸ�Ƿ����
	bool mIsEnd;

	/// ƽ�й�
	Light* mLight;

	///GUI
public:
	MyGUI::VectorWidgetPtr levelStageLayout;

	static const int cellCount = 3;
	static const int cellSize = 80;
	MyGUI::ImageBox* cellImage[cellCount];
	
	static const int imageCount = 3; 
	static const int imageSize = 40;
	MyGUI::ImageBox* bulletImage[imageCount];
	MyGUI::TextBox* bulletCount[imageCount];

	/// ��ʾEsc�����˵�
	void showEscMenu();
	/// ע����ʾEsc�˵�
	void unShowEscMenu();
	/// ���������
	MyGUI::VectorWidgetPtr mEdLayout;
	// ��������ص�����

	/// Esc�����
	MyGUI::VectorWidgetPtr mEdEscLayout;
protected:
	/// �����˵�
	void onEdHomeBtnClick(MyGUI::Widget* sender);

	/// ����
	/// @note �÷�����Ҫ�ɳ����ֱ�ʵ�֣���Ϊ�ض�������֪����Ҫ�����ĸ�����
	virtual void onEdReplayBtnClick(MyGUI::Widget* sender) = 0;

	/// ��һ��
	/// @note �÷�����Ҫ�ɳ����ֱ�ʵ�֣���Ϊ�ض�������֪����Ҫ�����ĸ�����
	virtual void onEdNextBtnClick(MyGUI::Widget* sender) = 0;

	void onEdBackToMenuBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdBackToMenuBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdReplayBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdReplayBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdNextBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdNextBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscBackToMenuBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscBackToMenuBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscResumeBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscResumeBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscExitBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscExitBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
};


#endif