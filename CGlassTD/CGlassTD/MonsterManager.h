#ifndef MonsterManager_h__
#define MonsterManager_h__
#include <list>
#include <windows.h>
#include "Monster.h"
#include "ParamParser.h"
#include "Bullet.h"
#include "Maze.h"


struct Wave
{
	float newWaveTime;
	int tatalMonster;
	int smallNormalMonster;
	int smallIceMonster;
	int smallFireMonster;
	int bigNormalMonster;
	int bigIceMonster;
	int bigFireMonster;
	float timeInteval1;
	float timeInteval2;
};
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
	static Maze* mMaze;
	/// ���ڼ�¼���б�ը�ӵ���Ϣ�Ľṹ��
	std::vector<ExplodedBulletsStruct*> mExplodeBulletsLists;
	/// ʱ�������
	static float mTimeCount;
	/// std::list<SceneNode*> mMonsterNodes;
	/// ���ڵĹ��﹤��
	static MonsterFactory* mCurrentMonsterFactory;
	/// ���޹����б��������ɲ�ͬ����Ĺ���
	static std::vector<MonsterFactory*> mMonsterFactoryList;
	/// �����б�
	static std::list<Monster*> mMonstersList;
	/// ��������
	static int mMonsterNum;
	/// �������������һ
	static MonsterManager* mMonsterMgr;

	/// ���������ʱ����
	static float mNewMonsterTime ;

	/// ��ʼ����־λ
	static bool isInitialized;

	//MonsterManager(Maze* maze);
	//MonsterManager(Ogre::SceneManager* sceneManager);
	MonsterManager();


	std::vector<Wave> mMonsterWave;

//protected:
//	
//	static DWORD WINAPI createMonstersThread(PVOID pVoid); 
		
public:
	static void initialize(Maze* maze);

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
	//static MonsterManager* getMonsterManager(Maze* maze);

	/// void monsterTimer(Ogre::SceneManager* sceneManager);

	/// ��������
	void monsterGenerate(Ogre::SceneManager* sceneManager, float timeSinceLastFrame);

	void setMaze(Maze* maze);

	/// ���汬ը�ڵ���Ϣ
	void storeExplodedBullets(std::vector<NameValueList> explodedBullets);

	/// ���¹�����Ϣ
	void updateState(std::vector<NameValueList> explodedBullets, float timeSinceLastFrame, Ogre::SceneManager* sceneManager);
	
	/// ���ù��޲���
	void setMonsterWave(String fileName);
};


#endif // MonsterManager_h__
