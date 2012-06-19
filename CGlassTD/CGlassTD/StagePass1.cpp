#include "StagePass1.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include <OgreLogManager.h>
#include "ParamParser.h"
#include <string>


StagePass1::StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui),
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

	//this->pushStep(new StagePass1Step0(this));
	this->pushStep(new StagePass1Step1(this));
	this->jumpToStep(0);

	///GUI
	my = MyGUI::LayoutManager::getInstance().loadLayout("my.layout");
	
	const int imageCount = 3; 
	const int imageSize = 40;
	MyGUI::ImageBox* bulletImage[imageCount];

	bulletImage[0] = this->getGUI()->findWidget<MyGUI::ImageBox>("bomb_red");
	bulletImage[1] = this->getGUI()->findWidget<MyGUI::ImageBox>("bomb_blue");
	bulletImage[2] = this->getGUI()->findWidget<MyGUI::ImageBox>("bomb_black");

	bulletImage[0]->setCoord((gui->getViewWidth()-4*imageSize),(gui->getViewHeight()-2*imageSize), imageSize*2, imageSize*2);
	bulletImage[1]->setCoord((gui->getViewWidth()-2*imageSize),(gui->getViewHeight()-1*imageSize), imageSize, imageSize);
	bulletImage[2]->setCoord((gui->getViewWidth()-1*imageSize),(gui->getViewHeight()-1*imageSize), imageSize, imageSize);

	MyGUI::TextBox* bulletCount[imageCount];
	bulletCount[0] = this->getGUI()->findWidget<MyGUI::TextBox>("b3");
	bulletCount[1] = this->getGUI()->findWidget<MyGUI::TextBox>("b2");
	bulletCount[2] = this->getGUI()->findWidget<MyGUI::TextBox>("b1");

	for(int i = 0; i < 3; i++)
	{

		std::ostringstream temp;
		temp << mCannon->getBulletFactories().at(i)->getAmmoCount();
		bulletCount[i]->setCaption(temp.str());
	}
	

	//MyGUI::ResourceManager::getInstance().load("Resources.xml");
	//MyGUI::ImageBox* image = MyGUI::Gui::getInstance().createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord(0, 0, 128, 128), MyGUI::Align::Default, "Main");
	//image->setItemResource("pic_Crystal_Clear_Butterfly");
	//image->setItemGroup("States");
	//image->setItemName("Normal");

	//image->setMaskPick("Crystal_Clear_Butterfly_Pick.png");
	/*image1->setItemResource("bomb_black.jpg");
	image2->setItemResource("bomb_blue.jpg");
	image3->setItemResource("bomb_red.jpg");

	image1->setMaskPick("bomb_pick.jpg");
	image2->setMaskPick("bomb_pick.jpg");
	image3->setMaskPick("bomb_pick.jpg");*/
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
