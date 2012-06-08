#include "StagePass1.h"
#include "StagePass1Step1.h"
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
	SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	Entity* cannon = sceneManager->createEntity((*cannonParams)["mesh"]);
	node->attachObject((MovableObject*)cannon);
	mCannon = new Cannon(node, cannon);
	if (cannonParams->find("material") != cannonParams->end())
		cannon->setMaterialName((*cannonParams)["material"]);
	std::vector<std::string> nums;
	if (cannonParams->find("position") != cannonParams->end())
	{
		nums = mysplit((*cannonParams)["position"]);
		node->setPosition((float)atof(nums[0].c_str()), (float)atof(nums[1].c_str()), (float)atof(nums[2].c_str()));
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
	// 炮台?
	SceneNode* node1 = sceneManager->getRootSceneNode()->createChildSceneNode();
	Entity* fort = sceneManager->createEntity("fort.mesh");
	node1->attachObject((MovableObject*)fort);
	node1->setPosition(0, 200, 550);

	// 给cannon增加炮弹
	ParamParser bulletParser = ParamParser("BulletDefine.xml");
	bulletParser.parse();
	bulletParser.moveToFirst();
	while (bulletParser.hasNext())
		mCannon->addBulletFactory(new BulletFactory(*bulletParser.getNext()));
	//mCannon->addBulletFactory(new BulletFactory());

	/// 加载迷宫地图
	/*const int mapWidth = 16;
	const int mapHeight = 16;
	int iMap[mapHeight *mapWidth] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 
		0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 
		1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 
		1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 
		1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 
		1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 
		0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 
		1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 
		1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 
		};*/
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
	mMaze = new Maze(sceneManager, map, mapWidth, mapHeight);

	/// 新增一个monster管理器
	mMonsterManager = MonsterManager::getMonsterManager(mMaze);

	/// 改变镜头视角
	//mCamera->lookAt(Vector3(0, 0, -100s));//lookat 貌似没用
	mCamera->setPosition(Vector3(0, 2000, 2000));
	mCamera->setDirection(-mCamera->getPosition());

	/// 设置天空盒
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");

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
