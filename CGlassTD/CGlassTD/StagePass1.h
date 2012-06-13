#ifndef StagePass1_h__
#define StagePass1_h__

#include "LevelStage.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"

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

	BulletManager mBulletManager;
	

	/// ��������
	Vector3 mGravity;

public:
	/// ���캯��
	/// @param pSceneManager ������������ָ��
	/// @param pStageManager ��̨��������ָ��
	StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass1(void);

	Cannon* getCannon();
	Maze* getMaze();
	MonsterManager* getMonsterManager();
	BulletManager& getBulletManager();
	Vector3 getGravity();
};

#endif // StagePass1_h__

