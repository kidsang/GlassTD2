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

class LevelStage : public Stage
{
public:
	/// ���캯��
	LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);

	/// ��������
	virtual ~LevelStage();

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

	// Get/Set
public:
	Cannon* getCannon()
	{
		return mCannon;
	}

	Maze* getMaze()
	{
		return mMaze;
	}

	MonsterManager* getMonsterManager()
	{
		return mMonsterManager;
	}

	BulletManager& getBulletManager()
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

protected:
	/// ��ǰ�ķֳ���
	Step* mCurrentStep;
	/// ��
	Cannon* mCannon;
	/// �Թ�
	Maze* mMaze;
	/// �������й�����
	MonsterManager* mMonsterManager;

	/// �ڵ�������
	BulletManager mBulletManager;
	/// ����������б�
	std::deque<Animator<Ogre::Camera>*> mCameraAnimatorList;

	/// ��������
	Vector3 mGravity;


};


#endif