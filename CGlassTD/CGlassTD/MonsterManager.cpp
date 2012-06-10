#include "MonsterManager.h"

MonsterManager* MonsterManager::mMonsterMgr = NULL;
int MonsterManager::mMonsterNum = 0;
float MonsterManager::mTimeCount = 0.0f;


MonsterManager::MonsterManager()
{
	ParamParser monsterParser = ParamParser("MonsterDefine.xml");
	monsterParser.parse();
	monsterParser.moveToFirst();
	while (monsterParser.hasNext())
		mMonsterFactoryList.push_back(new MonsterFactory(*monsterParser.getNext()));
	if(mMonsterFactoryList.size() != 0)
		mCurrentMonsterFactory = mMonsterFactoryList.at(0);
}

MonsterManager::MonsterManager( Maze* maze )
{
	ParamParser monsterParser = ParamParser("MonsterDefine.xml");
	monsterParser.parse();
	monsterParser.moveToFirst();
	while (monsterParser.hasNext())
		mMonsterFactoryList.push_back(new MonsterFactory(*monsterParser.getNext()));
	if(mMonsterFactoryList.size() != 0)
		mCurrentMonsterFactory = mMonsterFactoryList.at(0);

	mMaze = maze;
	i = 1;
}

MonsterManager::~MonsterManager(void)
{
	if(mMonsterMgr != NULL)
		delete mMonsterMgr;
	for (auto iter = mMonstersList.begin(); iter != mMonstersList.end(); ++iter)
		delete (*iter);
	for (auto iter = mMonsterFactoryList.begin(); iter != mMonsterFactoryList.end(); ++iter)
		delete (*iter);
	delete mCurrentMonsterFactory;
	delete mMaze;
}

MonsterManager* MonsterManager::getMonsterManager(void)
{
	if(mMonsterMgr == NULL)
		mMonsterMgr = new MonsterManager();
	return mMonsterMgr;
}

MonsterManager* MonsterManager::getMonsterManager(Maze* maze)
{
	if(mMonsterMgr == NULL)
		mMonsterMgr = new MonsterManager(maze);
	return mMonsterMgr;
}

//
//void MonsterManager::monsterTimer(Ogre::SceneManager* sceneManager)
//{
//	MonsterManager* monsterMgr = getMonterManager();
//	SetTimer(1, 3000, monsterMgr->monsterGenerate(sceneManager));
//}

void MonsterManager::monsterGenerate(Ogre::SceneManager* sceneManager, float timeSinceLastFrame)
{
	//::CreateThread(NULL, 0, createMonstersThread, sceneManager, NULL, NULL);
	mMonsterMgr->setTimeCount(mMonsterMgr->getTimeCount() + timeSinceLastFrame);
	/// std::list<Monster*> monsterList = mMonsterMgr->getMonstersList();
	if(mMonsterMgr->getTimeCount() > NEW_MONSTER_TIME || mMonsterMgr->getTimeCount() == NEW_MONSTER_TIME)
	{
		Monster* monster = mCurrentMonsterFactory->createInstance(sceneManager, mMaze);
		/// monster->monsterScale(0.1, 0.1, 0.1);
		monster->setAnimate();
		mMonstersList.push_back(monster);
		mMonsterMgr->MonsterNumPlus();
		mMonsterMgr->setTimeCount(0.0f);

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
//	///// MoveMemory(param, pVoid, sizeof(Ogre::SceneManager));
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
}

void MonsterManager::updateState( std::vector<NameValueList> explodedBullets, float timeSinceLastFrame, Ogre::SceneManager* sceneManager )
{
	/*if(i == 1)
	{
		mMonsterMgr->monsterGenerate(sceneManager, timeSinceLastFrame);i++;
	}*/
	mMonsterMgr->monsterGenerate(sceneManager, timeSinceLastFrame);

	NameValueList params;
	std::string bulletType;
	float bulletHarm;
	float bulletAppendHarm;
	float bulletRadius;
	float bulletEffectTime;
	float bulletPos[3];
	std::vector<std::string> bulletPosStrings;
	for(auto iter2 = mMonstersList.begin(); iter2 != mMonstersList.end(); ++iter2)
	{
		/// 如果怪物死亡，就销毁节点
		if((*iter2)->isMonsterDead())
		{
			(*iter2)->destroyItself();
			mMonstersList.erase(iter2++);

		}

		/// 遍历子弹
		for(auto iter = explodedBullets.begin(); iter != explodedBullets.end(); ++iter)
		{
			/// 获取炮弹数据，将其转换成应有类型
			/// 炮弹伤害
			if ((*iter).find("damage") != (*iter).end())
				bulletHarm = (float)atof((*iter)["damage"].c_str());
			/// 炮弹附加伤害
			if ((*iter).find("appendDamage") != (*iter).end())
				bulletAppendHarm = (float)atof((*iter)["appendDamage"].c_str());
			/// 炮弹半径范围
			if ((*iter).find("range") != (*iter).end())
				bulletRadius = (float)atof((*iter)["range"].c_str());
			/// 炮弹属性
			if ((*iter).find("spell") != (*iter).end())
				bulletType = ((*iter)["spell"].c_str());
			/// 炮弹效果持续时间
			if ((*iter).find("time") != (*iter).end())
				bulletEffectTime = (float)atof((*iter)["time"].c_str());
			/// 炮弹中心点位置
			if ((*iter).find("position") != (*iter).end())
			{	
				bulletPosStrings = mysplit((*iter)["position"]);
				bulletPos[0] = (float)atof(bulletPosStrings[0].c_str());
				bulletPos[1] = (float)atof(bulletPosStrings[1].c_str());
				bulletPos[2] = (float)atof(bulletPosStrings[2].c_str());

			}
		
		
			///(*iter2)->checkHitByBullet(bulletPos, bulletHarm, bulletAppendHarm, bulletEffectTime, bulletRadius, bulletType);
		}
		
		(*iter2)->go(timeSinceLastFrame);
		
		///(*iter2)->harmCheck(timeSinceLastFrame);
	}


	
}

void MonsterManager::setMaze( Maze* maze )
{
	mMaze = maze;
}
