#ifndef MonsterManager_h__
#define MonsterManager_h__
#include <list>
#include <windows.h>
#include "Monster.h"
#include "ParamParser.h"
#include "Bullet.h"
#include "Maze.h"
#include <vector>
#include "UFO.h"
#include "Stage.h"

/// ������ÿһ���������Ϣ
struct Wave
{
	float newWaveTime;
	int totalMonster;
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

/// ���������
/// ����������й���Ĵ������˶�������
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
	/// ��Ҫ���Ƴ��Ĺ����б�
	std::list<Monster*> mMonsterRemoveList;
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


	static std::vector<Wave> mMonsterWave ;

	/// ��ǰһ���ĺ���
	static int mCurrentWaveNum;
	/// ��ǰһ��
	static Wave mCurrentWave;
	/// ��������ţ��������滹��Ҫ�����ù���Ĺ���
	static std::vector<int> mMonsterFactoryRandom;
	/// ���ڵĹ�����
	static int mCurrentMonsterFactoryNum;

	UFO* mUFO;
	/// �Ƿ�ֹͣ��������
	static bool mIsStopGenerateMonster;

	/// ��һ���Ŀ�ʼ��־
	static bool mWaveIsBegin;

	static bool mWinGame;

//protected:
//	
//	static DWORD WINAPI createMonstersThread(PVOID pVoid); 

public:
	static void initialize(Maze* maze, const std::string& monsterDefine);

	~MonsterManager(void);
    /// Ogre::String mMonNames[100];
	/// ��ȡ��������
	int getMonsterNum(void);

	/// ���ù�������
	void setMonsterNum(int num);

	void removeNumByFactoryType(std::string type);

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

	/// ������ʼ
	void waveBegin();

	void setUFO(UFO* ufo);

	/// ɾ��ָ����Monster
	/// @note ��ɾ����һ�У������ڵ��ģ��
	void destoryMonster(Monster* monster);
	
	/// ����������
	/// ��Ϊ�����ǵ���
	/// add by kid
	void release();

	void setWinGame(bool misWin = true)
	{
		mWinGame = misWin;
	}

	void updateIsWin()
	{
		// ����ʤ������
		if(mCurrentWaveNum == mMonsterWave.size() && mMonstersList.size() == 0)
			mWinGame = true;
	}

	bool isWinGame()
	{
		return mWinGame;
	}
};


#endif // MonsterManager_h__
