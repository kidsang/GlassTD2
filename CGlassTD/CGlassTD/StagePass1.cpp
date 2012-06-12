#include "StagePass1.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include <OgreLogManager.h>
#include "ParamParser.h"

StagePass1::StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager)
	: LevelStage(sceneManager, stageManager),
	mGravity(Vector3(0, -200, 0))
{
	// 新增cannon
	ParamParser cannonParser= ParamParser("CannonDefine.xml");
	cannonParser.parse();
	cannonParser.moveToFirst();
	NameValueList* cannonParams = cannonParser.getNext(); 
	SceneNode* tireNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	SceneNode* gunNode = tireNode->createChildSceneNode();
	Entity* gun = sceneManager->createEntity((*cannonParams)["gunMesh"]);
	Entity* tire = sceneManager->createEntity((*cannonParams)["tireMesh"]);
	gunNode->attachObject((MovableObject*)gun);
	tireNode->attachObject((MovableObject*)tire);
	mCannon = new Cannon(gunNode, gun, tireNode, tire);
	/*if (cannonParams->find("material") != cannonParams->end())
		gun->setMaterialName((*cannonParams)["material"]);*/
	std::vector<std::string> nums;
	if (cannonParams->find("position") != cannonParams->end())
	{
		nums = mysplit((*cannonParams)["position"]);
		tireNode->setPosition((float)atof(nums[0].c_str()), (float)atof(nums[1].c_str()), (float)atof(nums[2].c_str()));
	}
	if (cannonParams->find("strength") != cannonParams->end())
		mCannon->setFireStrength((float)(atof((*cannonParams)["strength"].c_str())));
	if (cannonParams->find("colddown") != cannonParams->end())
		mCannon->setColdDown((float)(atof((*cannonParams)["colddown"].c_str())));
	if (cannonParams->find("offset") != cannonParams->end())
	{
		nums = mysplit((*cannonParams)["offset"]);
		mCannon->setFireOffset(Vector3((float)atof(nums[0].c_str()), (float)atof(nums[1].c_str()), (float)atof(nums[2].c_str())));
	}
	if (cannonParams->find("angle") != cannonParams->end())
	{
		nums = mysplit((*cannonParams)["angle"]);
		mCannon->setFireAngle(Vector2((float)atof(nums[0].c_str()), (float)atof(nums[1].c_str())));
	}
	//// 炮台?
	//SceneNode* node1 = sceneManager->getRootSceneNode()->createChildSceneNode();
	//Entity* fort = sceneManager->createEntity("fort.mesh");
	//node1->attachObject((MovableObject*)fort);
	//node1->setPosition(0, 200, 550);

	// 给cannon增加炮弹
	ParamParser bulletParser = ParamParser("BulletDefine.xml");
	bulletParser.parse();
	bulletParser.moveToFirst();
	while (bulletParser.hasNext())
		mCannon->addBulletFactory(new BulletFactory(*bulletParser.getNext()));

	/// 加载迷宫地图
	ParamParser mazeParser = ParamParser("MazeDefine.xml");
	mazeParser.parse();
	mazeParser.moveToFirst();
	NameValueList* mazeParams = mazeParser.getNext();
	int mapWidth = 2;
	int mapHeight = 2;
	if (mazeParams->find("width") != mazeParams->end())
		mapWidth = atoi((*mazeParams)["width"].c_str());
	if (mazeParams->find("height") != mazeParams->end())
		mapHeight = atoi((*mazeParams)["height"].c_str());
	int size = mapHeight * mapWidth;
	int* map = new int[size]();
	if (mazeParams->find("map") != mazeParams->end())
	{
		nums = mysplit((*mazeParams)["map"]);
		for (int i=0; i<size; i++)
			map[i] = atoi(nums[i].c_str());
	}	
	Ogre::Vector3 start1 = Ogre::Vector3();
	Ogre::Vector3 start2 = Ogre::Vector3();
	Ogre::Vector3 end = Ogre::Vector3();

	if(mazeParams->find("startPos") != mazeParams->end())
	{
		nums = mysplit((*mazeParams)["startPos"]);
		start1.x = atoi(nums[0].c_str());
		start1.y = atoi(nums[1].c_str());
		start1.z = atoi(nums[2].c_str());
		start2.x = atoi(nums[3].c_str());
		start2.y = atoi(nums[4].c_str());
		start2.z = atoi(nums[5].c_str());
	}
	if(mazeParams->find("finalPos") != mazeParams->end())
	{
		nums = mysplit((*mazeParams)["finalPos"]);
		end.x = atoi(nums[0].c_str());
		end.y = atoi(nums[1].c_str());
		end.z = atoi(nums[2].c_str());

	}
	
	mMaze = new Maze(sceneManager, map, mapWidth, mapHeight,start1, start2, end);

	/// 新增一个monster管理器
	mMonsterManager = MonsterManager::getMonsterManager(mMaze);


	/// 设置天空盒
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");

	// step
	//this->pushStep(new StagePass1Step0(this));
	this->pushStep(new StagePass1Step1(this));
	this->jumpToStep(0);
}


StagePass1::~StagePass1(void)
{
	// 删除炮
	delete mCannon;
	// 删除炮弹
	//mBulletList.clear();
	// 删除迷宫
	delete mMaze;
}


Cannon* StagePass1::getCannon()
{
	return mCannon;
}


Maze* StagePass1::getMaze()
{
	return mMaze;
}

MonsterManager* StagePass1::getMonsterManager()
{
	return mMonsterManager;
}

BulletManager& StagePass1::getBulletManager()
{
	return mBulletManager;
}

Vector3 StagePass1::getGravity()
{
	return mGravity;
}
