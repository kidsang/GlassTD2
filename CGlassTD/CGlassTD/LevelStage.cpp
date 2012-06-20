#include "LevelStage.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"

LevelStage::LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui),
	mCurrentStep(0), mCannon(0), mMaze(0), mMonsterManager(0), mUFO(0),
	mGravity(Vector3(0, -200, 0))
{
}

LevelStage::~LevelStage()
{
	if (mCurrentStep)
		delete mCurrentStep;
	if (mCannon)
		delete mCannon;
	if (mUFO)
		delete mUFO;
	if (mMaze)
		delete mMaze;
	// 单例
	if (mMonsterManager)
		mMonsterManager->release();
	for (auto iter = mCameraAnimatorList.begin(); iter != mCameraAnimatorList.end(); ++iter)
		delete (*iter);
}

void LevelStage::jumpToStep(Step* step)
{
	delete mCurrentStep;
	mCurrentStep = step;
	step->init();
}

bool LevelStage::run(float timeSinceLastFrame)
{
	// 播放摄像机动画
	// 丑陋的代码by kid
	{
		auto iter = mCameraAnimatorList.begin();
		if (iter != mCameraAnimatorList.end())
			if (!(*iter)->run(timeSinceLastFrame, mCamera))
			{
				jumpToStep(new StagePass1Step1(this));
				delete (*iter);
				mCameraAnimatorList.erase(iter);
				mMaze->clearShadow();
			}
	}

	return mCurrentStep->run(timeSinceLastFrame);
}

bool LevelStage::onKeyPressed(const OIS::KeyEvent &arg)
{
	return mCurrentStep->onKeyPressed(arg);
}

bool LevelStage::onMouseMoved(const OIS::MouseEvent &arg)
{
	return mCurrentStep->onMouseMoved(arg);
}

bool LevelStage::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return mCurrentStep->onMousePressed(arg, id);
}

bool LevelStage::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return mCurrentStep->onMouseReleased(arg, id);
}

void LevelStage::initializeCannon( const std::string& cannonDefine, const std::string& bulletDefine )
{
	// 新增cannon
	ParamParser cannonParser= ParamParser(cannonDefine);
	cannonParser.parse();
	cannonParser.moveToFirst();
	NameValueList* cannonParams = cannonParser.getNext(); 
	SceneNode* tireNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	SceneNode* gunNode = tireNode->createChildSceneNode();
	Entity* gun = mSceneManager->createEntity((*cannonParams)["gunMesh"]);
	Entity* tire = mSceneManager->createEntity((*cannonParams)["tireMesh"]);
	gunNode->attachObject((MovableObject*)gun);
	tireNode->attachObject((MovableObject*)tire);
	mCannon = new Cannon(gunNode, gun, tireNode, tire);
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

	// 给cannon增加炮弹
	ParamParser bulletParser = ParamParser(bulletDefine);
	bulletParser.parse();
	bulletParser.moveToFirst();
	while (bulletParser.hasNext())
		mCannon->addBulletFactory(new BulletFactory(*bulletParser.getNext()));
}

void LevelStage::initializeMaze( const std::string& mazeDefine, const std::string& cellDefine )
{
	/// 加载迷宫地图
	ParamParser mazeParser = ParamParser(mazeDefine);
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
	std::vector<std::string> nums;
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

	mMaze = new Maze(mSceneManager, map, mapWidth, mapHeight,start1, start2, end, cellDefine);
}

void LevelStage::initializeUFO( const std::string& ufoDefine )
{
	ParamParser parser= ParamParser(ufoDefine);
	parser.parse();
	parser.moveToFirst();
	NameValueList* params = parser.getNext(); 

	SceneNode* node = mSceneManager->getRootSceneNode()->createChildSceneNode();
	std::vector<std::string> nums;
	if (params->find("position") != params->end())
	{
		nums = mysplit((*params)["position"]);
		node->setPosition((float)atof(nums[0].c_str()), (float)atof(nums[1].c_str()), (float)atof(nums[2].c_str()));
	}
	Entity* entity = mSceneManager->createEntity((*params)["mesh"]);
	node->attachObject(entity);

	int blood = 0;
	if (params->find("blood") != params->end())
		blood = atoi((*params)["blood"].c_str());

	mUFO = new UFO(node, entity, blood);

	/// ufo头顶血条
	BillboardSet* healthHUD = mSceneManager->createBillboardSet();
	healthHUD->setMaterialName("Glass/Billboard");
	healthHUD->setDefaultWidth(200);
	healthHUD->setDefaultHeight(14);
	SceneNode* hudNode = node->createChildSceneNode();
	hudNode->attachObject(healthHUD);
	Billboard* b = healthHUD->createBillboard(0, entity->getBoundingBox().getSize().y, 0);
	b->setColour(ColourValue(0, 0.8f, 0));

	mUFO->setHealthHUD(healthHUD);

}
