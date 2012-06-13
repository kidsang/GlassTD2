#ifndef MonsterManager_h__
#define MonsterManager_h__
#include <list>
#include <windows.h>
#include "Monster.h"
#include "ParamParser.h"
#include "Bullet.h"
#include "Maze.h"

/// ���ڼ�¼��ը���ڵ��Ľṹ��
struct ExplodedBulletsStruct
{
	std::string bulletType;
	float bulletHarm;
	float bulletAppendHarm;
	float bulletRadius;
	float bulletEffectTime;
	float bulletPos[3];
};


class MonsterManager
{
private:
	/// ��ͼ
	Maze* mMaze;
	/// ���ڼ�¼���б�ը�ӵ���Ϣ�Ľṹ��
	std::vector<ExplodedBulletsStruct*> mExplodeBulletsLists;
	/// ʱ�������
	static float mTimeCount;
	/// std::list<SceneNode*> mMonsterNodes;
	/// ���ڵĹ��﹤��
	MonsterFactory* mCurrentMonsterFactory;
	/// ���޹����б��������ɲ�ͬ����Ĺ���
	std::vector<MonsterFactory*> mMonsterFactoryList;
	/// �����б�
	std::list<Monster*> mMonstersList;
	/// ��������
	static int mMonsterNum;
	/// �������������һ
	static MonsterManager* mMonsterMgr;

	/// ���������ʱ����
	float mNewMonsterTime ;

	MonsterManager(Maze* maze);
	MonsterManager(Ogre::SceneManager* sceneManager);
	MonsterManager();

//protected:
//	
//	static DWORD WINAPI createMonstersThread(PVOID pVoid); 
		
public:
	~MonsterManager(void);
    /// Ogre::String mMonNames[100];
	/// ��ȡ��������
	int getMonsterNum(void);

	/// ���ù�������
	void setMonsterNum(int num);

	/// ��������+1
	void MonsterNumPlus(void);

	/// ��ȡʱ���ۼӼ�������ֵ
	float getTimeCount(void);

	/// ����ʱ���ۼӼ�������ֵ
	void setTimeCount(float timeCount);

	/// ��ȡ�����б�
	std::list<Monster*> getMonstersList(void);

	/// ��ȡ���������
	static MonsterManager* getMonsterManager(void);
	static MonsterManager* getMonsterManager(Maze* maze);

	/// void monsterTimer(Ogre::SceneManager* sceneManager);

	/// ��������
	void monsterGenerate(Ogre::SceneManager* sceneManager, float timeSinceLastFrame);

	void setMaze(Maze* maze);

	/// ���汬ը�ڵ���Ϣ
	void storeExplodedBullets(std::vector<NameValueList> explodedBullets);

	/// ���¹�����Ϣ
	void updateState(std::vector<NameValueList> explodedBullets, float timeSinceLastFrame, Ogre::SceneManager* sceneManager);
};


#endif // MonsterManager_h__
