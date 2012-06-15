#ifndef StagePass1_h__
#define StagePass1_h__

#include "LevelStage.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"
#include "Animator.h"

/// ��һ�س���
class StagePass1 : public LevelStage
{
private:
	/// ��
	Cannon* mCannon;
	/// �����д��ڵ��ڵ����б�
	//MyList<Bullet*> mBulletList;
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

public:
	/// ���캯��
	/// @param pSceneManager ������������ָ��
	/// @param pStageManager ��̨��������ָ��
	StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass1(void);

	/// �����������߼�
	/// @param timeSinceLastFrame ����һ֡���������ŵ�ʱ��
	/// @note �������ÿһ֡���ã��������ÿһ֡���߼�
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool run(float timeSinceLastFrame);

	/// ���һ�����������
	void addCameraAnimator(Animator<Ogre::Camera>* ani)
	{
		mCameraAnimatorList.push_back(ani);
	}

	Cannon* getCannon();
	Maze* getMaze();
	MonsterManager* getMonsterManager();
	BulletManager& getBulletManager();
	Vector3 getGravity();
};

#endif // StagePass1_h__

