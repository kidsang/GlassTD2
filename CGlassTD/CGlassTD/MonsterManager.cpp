#include "MonsterManager.h"

MonsterManager* MonsterManager::mMonsterMgr = NULL;
int MonsterManager::mMonsterNum = 0;
float MonsterManager::mTimeCount = 0.0f;

bool MonsterManager::isInitialized = false;
Maze* MonsterManager::mMaze = 0;
MonsterFactory* MonsterManager::mCurrentMonsterFactory = 0;
std::vector<MonsterFactory*> MonsterManager::mMonsterFactoryList = std::vector<MonsterFactory*>();
std::list<Monster*> MonsterManager::mMonstersList = std::list<Monster*>();
float MonsterManager::mNewMonsterTime = 0;

MonsterManager::MonsterManager()
{
//	ParamParser monsterParser = ParamParser("MonsterDefine.xml");
//	monsterParser.parse();
//	monsterParser.moveToFirst();
//	NameValueList* monsterParams = monsterParser.getNext();
//	this->mNewMonsterTime = atof((*monsterParams)["Time"].c_str());
//	while (monsterParser.hasNext())
//		mMonsterFactoryList.push_back(new MonsterFactory(*monsterParser.getNext()));
//	if(mMonsterFactoryList.size() != 0)
//		mCurrentMonsterFactory = mMonsterFactoryList.at(3);
}

/*MonsterManager::MonsterManager( Maze* maze )
{
	ParamParser monsterParser = ParamParser("MonsterDefine.xml");
	monsterParser.parse();
	monsterParser.moveToFirst();
	NameValueList* monsterParams = monsterParser.getNext();
	this->mNewMonsterTime = atof((*monsterParams)["newMonsterTime"].c_str());
	while (monsterParser.hasNext())
		mMonsterFactoryList.push_back(new MonsterFactory(*monsterParser.getNext()));
	if(mMonsterFactoryList.size() != 0)
		mCurrentMonsterFactory = mMonsterFactoryList.at(0);

	mMaze = maze;
}*/

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
	assert(isInitialized);
	if(mMonsterMgr == NULL)
		mMonsterMgr = new MonsterManager();
	return mMonsterMgr;
}

/*MonsterManager* MonsterManager::getMonsterManager(Maze* maze)
{
	if(mMonsterMgr == NULL)
		mMonsterMgr = new MonsterManager(maze);
	return mMonsterMgr;
}*/

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
	if(mMonsterMgr->getTimeCount() > mNewMonsterTime || mMonsterMgr->getTimeCount() == mNewMonsterTime)
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
	mMonsterMgr->monsterGenerate(sceneManager, timeSinceLastFrame);

	for(auto iter2 = mMonstersList.begin(); iter2 != mMonstersList.end(); ++iter2)
	{
		/// ������������������ٽڵ�
		while((*iter2)->isMonsterDead())
		{
			(*iter2)->destroyItself();
			mMonstersList.erase(iter2++);
			if(iter2 == mMonstersList.end())
				break;

		}
		if(iter2 == mMonstersList.end())
			break;

		/// �����ӵ�
		for(auto iter = mExplodeBulletsLists.begin(); iter != mExplodeBulletsLists.end(); ++iter)
		{
			/// �Թ������ÿ���ڵ��ı���
			(*iter2)->checkHitByBullet((*iter)->bulletPos, (*iter)->bulletHarm, (*iter)->bulletAppendHarm, 
				(*iter)->bulletEffectTime, (*iter)->bulletRadius, (*iter)->bulletType);
		}
		/// �˺����
		(*iter2)->harmCheck(timeSinceLastFrame);
		/// ������
		(*iter2)->go(timeSinceLastFrame);
		
		
	}


	
}

void MonsterManager::setMaze( Maze* maze )
{
	mMaze = maze;
}

void MonsterManager::storeExplodedBullets(std::vector<NameValueList> explodedBullets)
{
	/// �������ÿո�ֽ�������Ϣ����ʱ����
	std::vector<std::string> bulletPosStrings;

	/// ���ڴ��浥���ڵ���Ϣ����ʱ����
	ExplodedBulletsStruct* explodedBulletsTemp;

	/// �����ӵ�,���������ڵ���Ϣ
	for(auto iter = explodedBullets.begin(); iter != explodedBullets.end(); ++iter)
	{
		explodedBulletsTemp = new ExplodedBulletsStruct();
		/// ��ȡ�ڵ����ݣ�����ת����Ӧ������
		/// �ڵ��˺�
		if ((*iter).find("damage") != (*iter).end())
			explodedBulletsTemp->bulletHarm = (float)atof((*iter)["damage"].c_str());
		/// �ڵ������˺�
		if ((*iter).find("appendDamage") != (*iter).end())
			explodedBulletsTemp->bulletAppendHarm = (float)atof((*iter)["appendDamage"].c_str());
		/// �ڵ��뾶��Χ
		if ((*iter).find("range") != (*iter).end())
			explodedBulletsTemp->bulletRadius = (float)atof((*iter)["range"].c_str());
		/// �ڵ�����
		if ((*iter).find("spell") != (*iter).end())
			explodedBulletsTemp->bulletType = ((*iter)["spell"].c_str());
		/// �ڵ�Ч������ʱ��
		if ((*iter).find("time") != (*iter).end())
			explodedBulletsTemp->bulletEffectTime = (float)atof((*iter)["time"].c_str());
		/// �ڵ����ĵ�λ��
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

void MonsterManager::initialize( Maze* maze )
{
	ParamParser monsterParser = ParamParser("MonsterDefine.xml");
	monsterParser.parse();
	monsterParser.moveToFirst();
	NameValueList* monsterParams = monsterParser.getNext();
	mNewMonsterTime = atof((*monsterParams)["newMonsterTime"].c_str());
	while (monsterParser.hasNext())
		mMonsterFactoryList.push_back(new MonsterFactory(*monsterParser.getNext()));
	if(mMonsterFactoryList.size() != 0)
		mCurrentMonsterFactory = mMonsterFactoryList.at(0);

	mMaze = maze;
	isInitialized = true;
}
