#include "MonsterManager.h"
#include "ParamParser.h"
#include "MonsterDeadAnimator.h"


MonsterManager* MonsterManager::mMonsterMgr = NULL;
int MonsterManager::mMonsterNum = 0;
float MonsterManager::mTimeCount = 0.0f;

bool MonsterManager::isInitialized = false;
Maze* MonsterManager::mMaze = 0;
MonsterFactory* MonsterManager::mCurrentMonsterFactory = 0;
std::vector<MonsterFactory*> MonsterManager::mMonsterFactoryList = std::vector<MonsterFactory*>();
std::list<Monster*> MonsterManager::mMonstersList = std::list<Monster*>();
float MonsterManager::mNewMonsterTime = 0;
std::vector<Wave> MonsterManager::mMonsterWave = std::vector<Wave>();
Wave MonsterManager::mCurrentWave = Wave();
std::vector<int> MonsterManager::mMonsterFactoryRandom = std::vector<int>();
int MonsterManager::mCurrentMonsterFactoryNum = 0;
int MonsterManager::mCurrentWaveNum = 0;
bool MonsterManager::mIsStopGenerateMonster = false;

MonsterManager::MonsterManager()
{
}

MonsterManager::~MonsterManager(void)
{
	release();
}

void MonsterManager::release()
{
	for (auto iter = mMonstersList.begin(); iter != mMonstersList.end(); ++iter)
		delete (*iter);
	mMonstersList.clear();
	for (auto iter = mMonsterFactoryList.begin(); iter != mMonsterFactoryList.end(); ++iter)
		delete (*iter);
	mMonsterFactoryList.clear();

	isInitialized = false;
}

MonsterManager* MonsterManager::getMonsterManager(void)
{
	assert(isInitialized);
	if(mMonsterMgr == NULL)
	{
		mMonsterMgr = new MonsterManager();
	}
	return mMonsterMgr;
}

void MonsterManager::monsterGenerate(Ogre::SceneManager* sceneManager, float timeSinceLastFrame)
{
	if(mIsStopGenerateMonster)
		return;
	/// 怪物波开始
	waveBegin();
	if(mIsStopGenerateMonster)
		return;
	//::CreateThread(NULL, 0, createMonstersThread, sceneManager, NULL, NULL);
	mMonsterMgr->setTimeCount(mMonsterMgr->getTimeCount() + timeSinceLastFrame);
	/// std::list<Monster*> monsterList = mMonsterMgr->getMonstersList();
	if(mMonsterMgr->getTimeCount() > mNewMonsterTime || mMonsterMgr->getTimeCount() == mNewMonsterTime)
	{
		Monster* monster = mCurrentMonsterFactory->createInstance(sceneManager, mMaze, this);
		/// monster->monsterScale(0.1, 0.1, 0.1);
		monster->setAnimate("Walk", true);
		mMonstersList.push_back(monster);
		mMonsterMgr->MonsterNumPlus();
		mMonsterMgr->setTimeCount(0.0f);
		mNewMonsterTime = Ogre::Math::RangeRandom(mCurrentWave.timeInteval1, mCurrentWave.timeInteval2);
		
	}
}
std::list<Monster*> MonsterManager::getMonstersList( void )
{
	return mMonstersList;
}




//
//DWORD WINAPI MonsterManager::createMonstersThread(PVOID pVoid)
//{
//	
//	
//	//Ogre::SceneManager* param = (Ogre::SceneManager*)pVoid;
//	///// param = (Ogre::SceneManager*)pVoid;
/// //MoveMemory(param, pVoid, sizeof(Ogre::SceneManager));
//	//Ogre::SceneManager* sceneManager = param;
//
//	//HANDLE mutex;
//	//mutex=::CreateMutex(NULL,FALSE,"MUTEX");
//	//
//	//MonsterGenerator* monsterGen = new MonsterGenerator();
//	//Ogre::String mesh = "penguin.mesh";
//	//for(int i = 0; i < 3; i++)
//	//{	
//	//	if(i == 2)
//	//		mesh = "robot.mesh";
//	//	//SetTimer(1, 3000, monsterGen().createMonster(sceneManager, mesh, monNames[i]));
//	//	::WaitForSingleObject(mutex,100);
//	//	if(mMonsterMgr == NULL)
//	//		break;
//	//	mMonsters->push_back(monsterGen->createMonster(sceneManager, mesh, mMonNames[i]));
//	//	Sleep(2000);
//	//	::ReleaseMutex(mutex);
//	//	
//	//}
//	return 0;
//}

float MonsterManager::getTimeCount(void)
{
	return mTimeCount;
}

void MonsterManager::setTimeCount(float timeCount)
{
	mTimeCount = timeCount;
}

int MonsterManager::getMonsterNum(void)
{
	return mMonsterNum;
}

void MonsterManager::setMonsterNum(int num)
{
	mMonsterNum = num;
}

void MonsterManager::MonsterNumPlus(void)
{
	mMonsterNum++;
	if(mCurrentMonsterFactory->getType() == "SmallNormalMonster")
		mCurrentWave.smallNormalMonster--;
	else if(mCurrentMonsterFactory->getType() == "SmallIceMonster")
		mCurrentWave.smallIceMonster--;
	else if(mCurrentMonsterFactory->getType() == "SmallFireMonster")
		mCurrentWave.smallFireMonster--;
	else if(mCurrentMonsterFactory->getType() == "BigNormalMonster")
		mCurrentWave.bigNormalMonster--;
	else if(mCurrentMonsterFactory->getType() == "BigIceMonster")
		mCurrentWave.bigIceMonster--;
	else if(mCurrentMonsterFactory->getType() == "BigFireMonster")
		mCurrentWave.bigFireMonster--;
	else
		;

	mCurrentWave.totalMonster--;

}

void MonsterManager::updateState( std::vector<NameValueList> explodedBullets, float timeSinceLastFrame, Ogre::SceneManager* sceneManager )
{
	mMonsterMgr->monsterGenerate(sceneManager, timeSinceLastFrame);

	/// 储存子弹信息
	storeExplodedBullets(explodedBullets);

	std::vector<Monster*> deadMonster;
	/// 遍历怪物
	for(auto iter2 = mMonstersList.begin(); iter2 != mMonstersList.end(); ++iter2)
	{
		/// 如果怪物死亡，就加入死亡列表
		if ((*iter2)->isMonsterDead())
		{
			/// 设置死亡动画
			(*iter2)->setAnimate("Die", true);
			deadMonster.push_back((*iter2));
			// 调用死亡动画
			MonsterDeadAnimator* mda = new MonsterDeadAnimator(0);
			mda->start((*iter2));
			(*iter2)->addAnimator(mda);
		}

		/// 遍历子弹
		for(auto iter = mExplodeBulletsLists.begin(); iter != mExplodeBulletsLists.end(); ++iter)
		{
			/// 对怪物进行每个炮弹的遍历
			(*iter2)->checkHitByBullet((*iter)->bulletPos, (*iter)->bulletHarm, (*iter)->bulletAppendHarm, 
				(*iter)->bulletEffectTime, (*iter)->bulletRadius, (*iter)->bulletType);
		}
		/// 伤害检测
		(*iter2)->harmCheck(timeSinceLastFrame);
		/// 怪物走
		(*iter2)->go(timeSinceLastFrame);		
		/// 怪物动画
		(*iter2)->animate(timeSinceLastFrame, (*iter2));
	}

	// 销毁monster
	for (auto iter = mMonsterRemoveList.begin(); iter != mMonsterRemoveList.end(); ++iter)
	{
		auto iter2 = std::find(mMonstersList.begin(), mMonstersList.end(), (*iter));
		if (iter2 != mMonstersList.end())
			mMonstersList.erase(iter2);
		delete (*iter);
	}
	mMonsterRemoveList.clear();


	
}

void MonsterManager::setMaze( Maze* maze )
{
	mMaze = maze;
}

void MonsterManager::storeExplodedBullets(std::vector<NameValueList> explodedBullets)
{
	/// 清空上次所有炮弹的信息
	mExplodeBulletsLists.clear();

	/// 用于利用空格分解坐标信息的临时变量
	std::vector<std::string> bulletPosStrings;

	/// 用于储存单个炮弹信息的临时变量
	ExplodedBulletsStruct* explodedBulletsTemp;

	/// 遍历子弹,储存所有炮弹信息
	for(auto iter = explodedBullets.begin(); iter != explodedBullets.end(); ++iter)
	{
		explodedBulletsTemp = new ExplodedBulletsStruct();
		/// 获取炮弹数据，将其转换成应有类型
		/// 炮弹伤害
		if ((*iter).find("damage") != (*iter).end())
			explodedBulletsTemp->bulletHarm = (float)atof((*iter)["damage"].c_str());
		/// 炮弹附加伤害
		if ((*iter).find("appendDamage") != (*iter).end())
			explodedBulletsTemp->bulletAppendHarm = (float)atof((*iter)["appendDamage"].c_str());
		/// 炮弹半径范围
		if ((*iter).find("range") != (*iter).end())
			explodedBulletsTemp->bulletRadius = (float)atof((*iter)["range"].c_str());
		/// 炮弹属性
		if ((*iter).find("spell") != (*iter).end())
			explodedBulletsTemp->bulletType = ((*iter)["spell"].c_str());
		/// 炮弹效果持续时间
		if ((*iter).find("time") != (*iter).end())
			explodedBulletsTemp->bulletEffectTime = (float)atof((*iter)["time"].c_str());
		/// 炮弹中心点位置
		if ((*iter).find("position") != (*iter).end())
		{	
			bulletPosStrings = mysplit((*iter)["position"]);
			explodedBulletsTemp->bulletPos[0] = (float)atof(bulletPosStrings[0].c_str());
			explodedBulletsTemp->bulletPos[1] = (float)atof(bulletPosStrings[1].c_str());
			explodedBulletsTemp->bulletPos[2] = (float)atof(bulletPosStrings[2].c_str());

		}
		mExplodeBulletsLists.push_back(explodedBulletsTemp);
	}

}

void MonsterManager::initialize( Maze* maze, const std::string& monsterDefine )
{
	ParamParser monsterParser = ParamParser(monsterDefine);
	monsterParser.parse();
	monsterParser.moveToFirst();
	NameValueList* monsterParams = monsterParser.getNext();
	mNewMonsterTime = atof((*monsterParams)["newMonsterTime"].c_str());
	while (monsterParser.hasNext())
	{
		mMonsterFactoryList.push_back(new MonsterFactory(*monsterParser.getNext()));
	}
	if(mMonsterFactoryList.size() != 0)
		mCurrentMonsterFactory = mMonsterFactoryList.at(0);
	
	mMaze = maze;
	isInitialized = true;
}

void MonsterManager::setMonsterWave( String fileName )
{
	ParamParser monsterWave = ParamParser(fileName);
	mMonsterWave.clear();
	monsterWave.parse();
	monsterWave.moveToFirst();
	NameValueList* waveParams ;
	while(monsterWave.hasNext())
	{
		waveParams = monsterWave.getNext();
		Wave wave;
		wave.newWaveTime = (atof((*waveParams)["newWaveTime"].c_str()));
		wave.totalMonster = (atoi((*waveParams)["total"].c_str()));
		wave.smallNormalMonster = (atoi((*waveParams)["smallNormalMonster"].c_str()));
		wave.smallIceMonster = (atoi((*waveParams)["smallIceMonster"].c_str()));
		wave.smallFireMonster = (atoi((*waveParams)["smallFireMonster"].c_str()));
		wave.bigNormalMonster = (atoi((*waveParams)["bigNormalMonster"].c_str()));
		wave.bigIceMonster = (atoi((*waveParams)["bigIceMonster"].c_str()));
		wave.bigFireMonster = (atoi((*waveParams)["smallFireMonster"].c_str()));
		wave.timeInteval1 = (atof((*waveParams)["timeInterval1"].c_str()));
		wave.timeInteval2  = (atof((*waveParams)["timeInterval2"].c_str()));
		mMonsterWave.push_back(wave);
	}

	mMonsterNum = 0;
	/// 不停止产怪
	mIsStopGenerateMonster = false;

	mCurrentWaveNum = 0;
	
	/// 设置当前波
	mCurrentWave = mMonsterWave[mCurrentWaveNum];
	mNewMonsterTime = mCurrentWave.newWaveTime;
	mMonsterFactoryRandom.clear();
	for(unsigned int i = 0; i < mMonsterFactoryList.size(); i++)
		mMonsterFactoryRandom.push_back(i);

}

void MonsterManager::setUFO( UFO* ufo )
{
	mUFO = ufo;
}

void MonsterManager::waveBegin()
{
	/// 对当前波的怪物数量进行判断，等于0的时候就进行下一波
	if(mCurrentWave.totalMonster == 0)
	{
		++mCurrentWaveNum;
		if((unsigned int)mCurrentWaveNum == mMonsterWave.size() || (unsigned int)mCurrentWaveNum > mMonsterWave.size())
		{
			mIsStopGenerateMonster = true;
			return;
		}
		mCurrentWave = mMonsterWave[mCurrentWaveNum];
		/// 将生成怪物的时间间隔设定为下一波的时间间隔
		mNewMonsterTime = mCurrentWave.newWaveTime;
		/// 清空随机工厂数
		mMonsterFactoryRandom.clear();
		for(unsigned int i = 0; i < mMonsterFactoryList.size(); i++)
			mMonsterFactoryRandom.push_back(i);

	}
	if(mCurrentWave.smallNormalMonster == 0)
	{	
		removeNumByFactoryType("SmallNormalMonster");
		mCurrentWave.smallNormalMonster--;
	}
	if(mCurrentWave.smallIceMonster == 0)
	{	
		removeNumByFactoryType("SmallIceMonster");
		mCurrentWave.smallIceMonster--;
	}
	if(mCurrentWave.smallFireMonster == 0)
	{
		removeNumByFactoryType("SmallFireMonster");
		mCurrentWave.smallFireMonster--;
	}
	if(mCurrentWave.bigNormalMonster == 0)
	{
		removeNumByFactoryType("BigNormalMonster");
		mCurrentWave.bigNormalMonster--;
	}
	if(mCurrentWave.bigIceMonster == 0)
	{
		removeNumByFactoryType("BigIceMonster");
		mCurrentWave.bigIceMonster--;
	}
	if(mCurrentWave.bigFireMonster == 0)
	{
		removeNumByFactoryType("BigFireMonster");
		mCurrentWave.bigFireMonster--;
	}
	if(mMonsterFactoryRandom.size() > 0)
	{
		srand(time(0));
		/// 将随机化的工厂号放在当前工厂号
		mCurrentMonsterFactoryNum = mMonsterFactoryRandom[rand() % mMonsterFactoryRandom.size()];
		mCurrentMonsterFactory = mMonsterFactoryList[mCurrentMonsterFactoryNum];
	}
}

void MonsterManager::removeNumByFactoryType( std::string type )
{
	int numMark = 0;
	for(auto iter = mMonsterFactoryList.begin(); iter != mMonsterFactoryList.end(); ++iter)
	{
		if((*iter)->getType() == type)
			break;
		numMark++;
	}
	/*for(auto iter = mMonsterFactoryRandom.begin(); iter != mMonsterFactoryRandom.end(); ++iter)
	{
	if((*iter) == numMark)
	{	
	mMonsterFactoryRandom.erase(iter);
	break;
	}
	}*/
	auto iter = std::find(mMonsterFactoryRandom.begin(), mMonsterFactoryRandom.end(), numMark);
	mMonsterFactoryRandom.erase(iter);
}

void MonsterManager::destoryMonster( Monster* monster )
{
	auto iter = std::find(mMonsterRemoveList.begin(), mMonsterRemoveList.end(), monster);
	if(iter == mMonsterRemoveList.end())
		mMonsterRemoveList.push_back(monster);
}
