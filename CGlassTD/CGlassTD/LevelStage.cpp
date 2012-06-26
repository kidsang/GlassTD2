#include "LevelStage.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StartStage.h"
#include "Money.h"

LevelStage::LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui, int level)
	: Stage(sceneManager, stageManager, gui),
	mCurrentStep(0), mCannon(0), mMaze(0), mMonsterManager(0), mUFO(0),
	mGravity(Vector3(0, -200, 0)), mIsRunning(true),mLevel(level)
{
	if (Money::getInstance() == 0)
		Money::init(gui);
	Money::getInstance()->display();
	// 结束画面
	MyGUI::ImageBox* backToMenu;
	MyGUI::ImageBox* palyAgain;
	MyGUI::ImageBox* nextStage;
	mEdLayout = MyGUI::LayoutManager::getInstance().loadLayout("passStage.layout");
	backToMenu = mGui->findWidget<MyGUI::ImageBox>("back_to_menu");
	backToMenu->eventMouseButtonPressed += MyGUI::newDelegate(this, &LevelStage::onEdBackToMenuBtnPress);
	backToMenu->eventMouseButtonReleased += MyGUI::newDelegate(this, &LevelStage::onEdBackToMenuBtnRelease);
	nextStage = mGui->findWidget<MyGUI::ImageBox>("next_one");
	nextStage->eventMouseButtonPressed += MyGUI::newDelegate(this, &LevelStage::onEdNextBtnPress);
	nextStage->eventMouseButtonReleased += MyGUI::newDelegate(this, &LevelStage::onEdNextBtnRelease);
	palyAgain = mGui->findWidget<MyGUI::ImageBox>("play_it_again");
	palyAgain->eventMouseButtonPressed += MyGUI::newDelegate(this, &LevelStage::onEdReplayBtnPress);
	palyAgain->eventMouseButtonReleased += MyGUI::newDelegate(this, &LevelStage::onEdReplayBtnRelease);
	mGui->findWidget<MyGUI::Window>("ed_window")->setPosition(270,200);
	mGui->findWidget<MyGUI::Window>("ed_window")->setVisible(false);

	levelStageLayout = MyGUI::LayoutManager::getInstance().loadLayout("my.layout");
}

LevelStage::~LevelStage()
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mEdLayout);
	MyGUI::LayoutManager::getInstance().unloadLayout(levelStageLayout);
	if (mCurrentStep)
	{
		delete mCurrentStep;
		mCurrentStep = 0;
	}
	if (mCannon)

	{
		delete mCannon;
		mCannon = 0;
	}
	if (mUFO)
	{
		delete mUFO;
		mUFO = 0;
	}
	if (mMaze)
	{
		delete mMaze;
		mMaze = 0;
	}
	// 单例
	if (mMonsterManager)
		mMonsterManager->release();
	for (auto iter = mCameraAnimatorList.begin(); iter != mCameraAnimatorList.end(); ++iter)
		delete (*iter);
	if(mWallType)
	{
		delete[] mWallType;
	}
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
	//updateMoney();
	return mCurrentStep->run(timeSinceLastFrame);
}

bool LevelStage::onKeyPressed(const OIS::KeyEvent &arg)
{
	return mCurrentStep->onKeyPressed(arg);
}

bool LevelStage::onMouseMoved(const OIS::MouseEvent &arg)
{
	// 鼠标滚轮拉远拉近
	mCamera->move(Vector3(0, arg.state.Z.rel*0.6, arg.state.Z.rel));

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

	mWallType = new String[3];
	mazeParams = mazeParser.getNext();
	if (mazeParams->find("wall1") != mazeParams->end())
		mWallType[0] = (*mazeParams)["wall1"];
	if (mazeParams->find("wall2") != mazeParams->end())
		mWallType[1] = (*mazeParams)["wall2"];
	if (mazeParams->find("wall3") != mazeParams->end())
		mWallType[2] = (*mazeParams)["wall3"];
	mMaze = new Maze(mSceneManager, map, mapWidth, mapHeight,start1, start2, end, cellDefine,mWallType);
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

void LevelStage::createGUI0()
{
	MyGUI::Gui* mGui = this->getGUI();
	
	cellImage[0] = mGui->findWidget<MyGUI::ImageBox>("swamp");
	cellImage[1] = mGui->findWidget<MyGUI::ImageBox>("spikeweed");
	cellImage[2] = mGui->findWidget<MyGUI::ImageBox>("trap");

	MyGUI::RenderManager* rm = MyGUI::RenderManager::getInstancePtr();
	cellImage[0]->setPosition(0,rm->getViewSize().height-cellImage[0]->getHeight());
	cellImage[1]->setPosition(cellImage[0]->getLeft()+cellImage[0]->getWidth(),rm->getViewSize().height-cellImage[0]->getHeight());
	cellImage[2]->setPosition(cellImage[1]->getLeft()+cellImage[1]->getWidth(),rm->getViewSize().height-cellImage[0]->getHeight());

	cellImage[0]->setVisible(true);
	cellImage[1]->setVisible(true);
	cellImage[2]->setVisible(true);

}
void LevelStage::createGUI1()
{
	MyGUI::Gui* mGui = this->getGUI();
	

	bulletImage[0] = mGui->findWidget<MyGUI::ImageBox>("bomb_red");
	bulletImage[1] = mGui->findWidget<MyGUI::ImageBox>("bomb_blue");
	bulletImage[2] = mGui->findWidget<MyGUI::ImageBox>("bomb_black");

	MyGUI::RenderManager* rm = MyGUI::RenderManager::getInstancePtr();
	bulletImage[0]->setCoord((rm->getViewSize().width-4*imageSize),(rm->getViewSize().height-2*imageSize), imageSize*2, imageSize*2);
	bulletImage[1]->setCoord((rm->getViewSize().width-2*imageSize),(rm->getViewSize().height-1*imageSize), imageSize, imageSize);
	bulletImage[2]->setCoord((rm->getViewSize().width-1*imageSize),(rm->getViewSize().height-1*imageSize), imageSize, imageSize);

	bulletCount[0] = mGui->findWidget<MyGUI::TextBox>("b3");
	bulletCount[1] = mGui->findWidget<MyGUI::TextBox>("b2");
	bulletCount[2] = mGui->findWidget<MyGUI::TextBox>("b1");

	for(int i = 0; i < 3; i++)
	{

		std::ostringstream temp;
		temp << this->getCannon()->getBulletFactories().at(i)->getAmmoCount();
		bulletCount[i]->setCaption(temp.str());
	}

	bulletImage[0]->setVisible(true);
	bulletImage[1]->setVisible(true);
	bulletImage[2]->setVisible(true);
}


void LevelStage::updateCount()
{
	MyGUI::Gui* mGui = this->getGUI();
	
	bulletCount[0] = mGui->findWidget<MyGUI::TextBox>("b3");
	bulletCount[1] = mGui->findWidget<MyGUI::TextBox>("b2");
	bulletCount[2] = mGui->findWidget<MyGUI::TextBox>("b1");

	for(int i = 0; i < 3; i++)
	{
		std::ostringstream temp;
		temp << this->getCannon()->getBulletFactories().at(i)->getAmmoCount();
		bulletCount[i]->setCaption(temp.str());
	}
}

void LevelStage::updateImage()
{
	MyGUI::Gui* mGui = this->getGUI();

	bulletImage[0] = mGui->findWidget<MyGUI::ImageBox>("bomb_red");
	bulletImage[1] = mGui->findWidget<MyGUI::ImageBox>("bomb_blue");
	bulletImage[2] = mGui->findWidget<MyGUI::ImageBox>("bomb_black");

	int Big = bulletImage[0]->getWidth()>bulletImage[1]->getWidth()?0:1;
	Big = bulletImage[Big]->getWidth()>bulletImage[2]->getWidth()?Big:2;
	int Next = (Big+1)%3;
	int left = bulletImage[0]->getCoord().left;
	int top = bulletImage[Big]->getCoord().top;

	int flag[imageCount] = {0,0,0};
	flag[Big] = 1;
	flag[Next] = -1;
	bulletImage[0]->setCoord(left,bulletImage[0]->getCoord().top+flag[0]*imageSize, (bulletImage[0]->getWidth()-flag[0]*imageSize), (bulletImage[0]->getHeight()-flag[0]*imageSize));
	bulletImage[1]->setCoord(bulletImage[0]->getCoord().left+bulletImage[0]->getWidth(),bulletImage[1]->getCoord().top+flag[1]*imageSize, (bulletImage[1]->getWidth()-flag[1]*imageSize), (bulletImage[1]->getHeight()-flag[1]*imageSize));
	bulletImage[2]->setCoord(bulletImage[1]->getCoord().left+bulletImage[1]->getWidth(),bulletImage[2]->getCoord().top+flag[2]*imageSize, (bulletImage[2]->getWidth()-flag[2]*imageSize), (bulletImage[2]->getHeight()-flag[2]*imageSize));

}

void LevelStage::change0to1()
{
	cellImage[0]->setVisible(false);
	cellImage[1]->setVisible(false);
	cellImage[2]->setVisible(false);
}


void LevelStage::onEdHomeBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StartStage(mSceneManager, mStageManager, mGui));
}

void LevelStage::onEdReplayBtnPress( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_id.toValue() != 0)
		return;
	MyGUI::ImageBox* temp = mGui->findWidget<MyGUI::ImageBox>("play_it_again");
	temp->setImageTexture("againPress.png");
}

void LevelStage::onEdReplayBtnRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_id.toValue() != 0)
		return;
	MyGUI::ImageBox* temp = mGui->findWidget<MyGUI::ImageBox>("play_it_again");
	temp->setImageTexture("again.png");
	onEdReplayBtnClick(_sender);
}

void LevelStage::onEdNextBtnPress( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_id.toValue() != 0)
		return;
	MyGUI::ImageBox* temp = mGui->findWidget<MyGUI::ImageBox>("next_one");
	temp->setImageTexture("nextStagePress.png");
}

void LevelStage::onEdNextBtnRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_id.toValue() != 0)
		return;
	MyGUI::ImageBox* temp = mGui->findWidget<MyGUI::ImageBox>("next_one");
	temp->setImageTexture("nextStage.png");
	onEdNextBtnClick(_sender);
}

void LevelStage::onEdBackToMenuBtnPress( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_id.toValue() != 0)
		return;
	MyGUI::ImageBox* backToMenu = mGui->findWidget<MyGUI::ImageBox>("back_to_menu");
	backToMenu->setImageTexture("backToMenuPress.png");
}

void LevelStage::onEdBackToMenuBtnRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_id.toValue() != 0)
		return;
	MyGUI::ImageBox* backToMenu = mGui->findWidget<MyGUI::ImageBox>("back_to_menu");
	backToMenu->setImageTexture("backToMenu.png");
	onEdHomeBtnClick(_sender);
}

int LevelStage::getLevel()
{
	return mLevel;
}
