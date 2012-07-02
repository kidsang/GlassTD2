#include "StagePass1Step1.h"
#include "Questions.h"
#include "Sound.h"
#include "GameResource.h"

StagePass1Step1::StagePass1Step1(LevelStage* stagePass1)
	: mStagePass1(stagePass1),
	mCameraZoom(0), mIsMoving(1),
	mAutoLimit(0)
{
	this->mStagePass1->createGUI1();
}

void StagePass1Step1::init()
{
	mStagePass1->getCamera()->setPosition(Vector3(0, 1000, 1800));
	mStagePass1->getCamera()->lookAt(Vector3(0, 0, 0));

	int level = mStagePass1->getLevel();
	switch (level)
	{
	case 1:
		Stage::playMusic("../Media/Sound/pass1.mp3", true);
		break;
	case 2:
		Stage::playMusic("../Media/Sound/pass2.mp3", true);
		break;
	case 3:
		Stage::playMusic("../Media/Sound/pass3.mp3", true);
		break;
	case 4:
		Stage::playMusic("../Media/Sound/pass3.mp3", true);
		break;
	case 5:
		Stage::playMusic("../Media/Sound/pass3.mp3", true);
		break;
	case 6:
		Stage::playMusic("../Media/Sound/pass3.mp3", true);
		break;
	}
}

bool StagePass1Step1::run(float timeSinceLastFrame)
{
	MonsterManager* monsterManager = mStagePass1->getMonsterManager();

	// 飞船爆了，要弹出一个框框，上面有两个按钮：返回主菜单和重玩
	if (mStagePass1->isRunning() && mStagePass1->getUFO()->isDestroy())
	{
		// 先终止所有声音
		Stage::stopAllSounds();

		mStagePass1->setEnd(true);
		// 如果正处于答题阶段，强制终止答题先
		if (Questions::getInstance()->isAnswering())
			Questions::getInstance()->giveUp();
		
		MyGUI::PointerManager::getInstance().setVisible(true);
		mStagePass1->setRunning(false);
		Stage::playSound("../Media/Sound/lose.wav", false);
		MyGUI::ImageBox* stages = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("word_of_stages");
		stages->setImageTexture(GameResource::WORD_OF_STAGE[mStagePass1->getLevel() - 1]);
		MyGUI::ImageBox* result = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("result_of_play");
		result->setImageTexture(GameResource::WORD_RESULT_FAIL);
		mStagePass1->getGUI()->findWidget<MyGUI::Window>("ed_window")->setVisible(true);
		mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("next_one")->setImageTexture("nextStageUnuse.png");
		mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("next_one")->setEnabled(false);
	}

	// 游戏胜利
	else if (mStagePass1->isRunning() && monsterManager->isWinGame())
	{
		// 先终止所有声音
		Stage::stopAllSounds();

		mStagePass1->setEnd(true);
	
		// 如果正处于答题阶段，强制终止答题先
		if (Questions::getInstance()->isAnswering())
			Questions::getInstance()->giveUp();
	
		MyGUI::PointerManager::getInstance().setVisible(true);
		mStagePass1->setRunning(false);
		Stage::playSound("../Media/Sound/win.wav", false);
		MyGUI::ImageBox* stages = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("word_of_stages");
		stages->setImageTexture(GameResource::WORD_OF_STAGE[mStagePass1->getLevel() - 1]);
		MyGUI::ImageBox* result = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("result_of_play");
		result->setImageTexture(GameResource::WORD_RESULT_SUCCESS);
		mStagePass1->getGUI()->findWidget<MyGUI::Window>("ed_window")->setVisible(true);
	}

	else if (mStagePass1->isRunning())
	{
		BulletManager* bulletManager = mStagePass1->getBulletManager();
		Vector3 gravity = mStagePass1->getGravity();
		// 发射曳光弹
		Bullet* tracer = mStagePass1->getCannon()->fireTracer(SceneManagerContainer::getSceneManager());
		if (tracer)
			bulletManager->add(tracer);
		bulletManager->fly(timeSinceLastFrame, gravity);

		Maze* maze = mStagePass1->getMaze();
		std::vector<NameValueList> explodedBullets = bulletManager->getAndRemoveExplodedBullets(maze->getHorizon(), SceneManagerContainer::getSceneManager());
		monsterManager->updateState(
			explodedBullets,
			timeSinceLastFrame,
			SceneManagerContainer::getSceneManager()
			);

		bulletManager->runExplodeAnimator(timeSinceLastFrame);

		if (mIsMoving == 1)
		{
			mStagePass1->getCannon()->move(Ogre::Vector3(-10, 0, 0));
			mStagePass1->getCamera()->move(Ogre::Vector3(-10, 0, 0));
			mAutoLimit -= 10;
			if (mAutoLimit < -1200)
				mIsMoving = 2;
		}
		if (mIsMoving == 2)
		{
			mStagePass1->getCannon()->move(Ogre::Vector3(10, 0, 0));
			mStagePass1->getCamera()->move(Ogre::Vector3(10, 0, 0));
			mAutoLimit += 10;
			if (mAutoLimit > 1200)
				mIsMoving = 1;
		}
	}
	
		
	return (!mStagePass1->getQuitFlag());
}

bool StagePass1Step1::onKeyPressed(const OIS::KeyEvent& arg)
{
	if(!mStagePass1->getKeyboardController())
		return true;
	// 处于答题阶段时无法进行操作
	if (Questions::getInstance()->isAnswering()) return true;

	// 发炮
	if (arg.key == OIS::KC_SPACE)
	{
		Bullet* bullet = mStagePass1->getCannon()->fire(SceneManagerContainer::getSceneManager());
		if (bullet)
		{
			mStagePass1->getBulletManager()->add(bullet);
			Stage::playSound("../Media/Sound/fire.wav", false);
			mStagePass1->updateCount();
		}
	}
	// 换炮弹
	else if (arg.key == OIS::KC_TAB)
	{
		Stage::playSound("../Media/Sound/switch.wav", false);
		mStagePass1->getCannon()->changeBullet();

		mStagePass1->updateImage(); 
		
	}
	else if (arg.key >= OIS::KC_1 && arg.key <= OIS::KC_9)
	{
		Stage::playSound("../Media/Sound/switch.wav", false);
		mStagePass1->getCannon()->changeBullet(arg.key - OIS::KC_1);
	}
	// 答题
	else if (arg.key == OIS::KC_Q && !mStagePass1->isEnd())
		Questions::getInstance()->popUpQuestion();
	// test by kid
	else if (arg.key == OIS::KC_L)
		mStagePass1->getUFO()->setBlood(-1);
	else if(arg.key == OIS::KC_ESCAPE)
	{
		mStagePass1->showEscMenu();
	}
	// 一键胜利 by neng
	else if(arg.key == OIS::KC_K)
	{
		MonsterManager* monsterManager = mStagePass1->getMonsterManager();
		monsterManager->setWinGame();
	}
	/*else if(arg.key == OIS::KC_A)
	{
		mIsMoving = 1;
	}
	else if(arg.key == OIS::KC_D)
	{
		mIsMoving = 2;
	}*/
	return true;
}

bool StagePass1Step1::onKeyReleased(const OIS::KeyEvent &arg)
{
	/*if (mIsMoving == 1 && arg.key == OIS::KC_A
		|| mIsMoving == 2 && arg.key == OIS::KC_D)
		mIsMoving = 0;*/
	return true;
}

bool StagePass1Step1::onMouseMoved(const OIS::MouseEvent& arg)
{
	if(!mStagePass1->getKeyboardController())
		return true;
	// 处于答题阶段时无法进行操作
	if (Questions::getInstance()->isAnswering()) return true;

	// 鼠标滚轮拉远拉近
	int zoom = arg.state.Z.rel;
	mCameraZoom += zoom;
	if (mCameraZoom < -1000)
	{
		zoom += -1000 - mCameraZoom;
		mCameraZoom = -1000;
	}
	else if (mCameraZoom > 0)
	{
		zoom += 0 - mCameraZoom;
		mCameraZoom = 0;
	}
	mStagePass1->getCamera()->move(Vector3(0, zoom*0.6, zoom));
	// 控制大炮
	mStagePass1->getCannon()->rotate(-arg.state.X.rel, arg.state.Y.rel, mStagePass1->getCamera());
	return true;
}

bool StagePass1Step1::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool StagePass1Step1::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}