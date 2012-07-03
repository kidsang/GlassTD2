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

/// 定义了每一波怪物的信息
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
/// 用于记录爆炸的炮弹的结构体
struct ExplodedBulletsStruct
{
	std::string bulletType;
	float bulletHarm;
	float bulletAppendHarm;
	float bulletRadius;
	float bulletEffectTime;
	float bulletPos[3];
};

/// 怪物管理类
/// 负责管理场景中怪物的创建、运动和销毁
class MonsterManager
{
private:
	/// 地图
	static Maze* mMaze;
	/// 用于记录所有爆炸子弹信息的结构体
	std::vector<ExplodedBulletsStruct*> mExplodeBulletsLists;
	/// 时间计数器
	static float mTimeCount;
	/// std::list<SceneNode*> mMonsterNodes;
	/// 现在的怪物工厂
	static MonsterFactory* mCurrentMonsterFactory;
	/// 怪兽工厂列表，用于生成不同种类的怪物
	static std::vector<MonsterFactory*> mMonsterFactoryList;
	/// 怪物列表
	static std::list<Monster*> mMonstersList;
	/// 需要被移除的怪物列表
	std::list<Monster*> mMonsterRemoveList;
	/// 怪物数量
	static int mMonsterNum;
	/// 怪物管理器，单一
	static MonsterManager* mMonsterMgr;

	/// 新增怪物的时间间隔
	static float mNewMonsterTime ;

	/// 初始化标志位
	static bool isInitialized;

	//MonsterManager(Maze* maze);
	//MonsterManager(Ogre::SceneManager* sceneManager);
	MonsterManager();


	static std::vector<Wave> mMonsterWave ;

	/// 当前一波的号码
	static int mCurrentWaveNum;
	/// 当前一波
	static Wave mCurrentWave;
	/// 工厂随机号，用来储存还需要生产该怪物的工厂
	static std::vector<int> mMonsterFactoryRandom;
	/// 现在的工厂号
	static int mCurrentMonsterFactoryNum;

	UFO* mUFO;
	/// 是否停止产生怪物
	static bool mIsStopGenerateMonster;

	/// 这一波的开始标志
	static bool mWaveIsBegin;

	static bool mWinGame;

//protected:
//	
//	static DWORD WINAPI createMonstersThread(PVOID pVoid); 

public:
	static void initialize(Maze* maze, const std::string& monsterDefine);

	~MonsterManager(void);
    /// Ogre::String mMonNames[100];
	/// 获取怪物数量
	int getMonsterNum(void);

	/// 设置怪物数量
	void setMonsterNum(int num);

	void removeNumByFactoryType(std::string type);

	/// 怪物数量+1
	void MonsterNumPlus(void);

	/// 获取时间累加计数器的值
	float getTimeCount(void);

	/// 设置时间累加计数器的值
	void setTimeCount(float timeCount);

	/// 获取怪物列表
	std::list<Monster*> getMonstersList(void);

	/// 获取怪物管理器
	static MonsterManager* getMonsterManager(void);
	//static MonsterManager* getMonsterManager(Maze* maze);

	/// void monsterTimer(Ogre::SceneManager* sceneManager);

	/// 怪物生成
	void monsterGenerate(Ogre::SceneManager* sceneManager, float timeSinceLastFrame);

	void setMaze(Maze* maze);

	/// 储存爆炸炮弹信息
	void storeExplodedBullets(std::vector<NameValueList> explodedBullets);

	/// 更新怪物信息
	void updateState(std::vector<NameValueList> explodedBullets, float timeSinceLastFrame, Ogre::SceneManager* sceneManager);
	
	/// 设置怪兽波数
	void setMonsterWave(String fileName);

	/// 波数开始
	void waveBegin();

	void setUFO(UFO* ufo);

	/// 删除指定的Monster
	/// @note 会删除其一切，包括节点和模型
	void destoryMonster(Monster* monster);
	
	/// 进行清理工作
	/// 因为该类是单例
	/// add by kid
	void release();

	void setWinGame(bool misWin = true)
	{
		mWinGame = misWin;
	}

	void updateIsWin()
	{
		// 更新胜利条件
		if(mCurrentWaveNum == mMonsterWave.size() && mMonstersList.size() == 0)
			mWinGame = true;
	}

	bool isWinGame()
	{
		return mWinGame;
	}
};


#endif // MonsterManager_h__
