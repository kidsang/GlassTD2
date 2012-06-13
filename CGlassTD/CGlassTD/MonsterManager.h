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


	std::vector<Wave> mMonsterWave;

//protected:
//	
//	static DWORD WINAPI createMonstersThread(PVOID pVoid); 
		
public:
	static void initialize(Maze* maze);

	~MonsterManager(void);
    /// Ogre::String mMonNames[100];
	/// 获取怪物数量
	int getMonsterNum(void);

	/// 设置怪物数量
	void setMonsterNum(int num);

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
};


#endif // MonsterManager_h__
