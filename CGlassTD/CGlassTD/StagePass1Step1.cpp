#include "StagePass1Step1.h"
#include "Questions.h"

#include "Sound.h"


StagePass1Step1::StagePass1Step1(LevelStage* stagePass1)
	: mStagePass1(stagePass1)
{
	this->mStagePass1->createGUI1();
}

void StagePass1Step1::init()
{

	mStagePass1->getCamera()->setPosition(Vector3(0, 1200, 2000));
	mStagePass1->getCamera()->lookAt(Vector3(0, 0, 0));
	//mStagePass1->getCamera()->setDirection(Vector3(0, -500, -1000));
}

bool StagePass1Step1::run(float timeSinceLastFrame)
{
	MonsterManager* monsterManager = mStagePass1->getMonsterManager();

	// 飞船爆了，要弹出一个框框，上面有两个按钮：返回主菜单和重玩
	if (mStagePass1->isRunning() && mStagePass1->getUFO()->isDestroy())
	{
		mStagePass1->setRunning(false);
		Sound::getInstance()->play("../Media/Sound/lose.wav", false);
		MyGUI::ImageBox* stages = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("word_of_stages");
		switch(mStagePass1->getLevel())
		{
		case 1:
			stages->setImageTexture("word_stage1.png");
			break;
		case 2:
			stages->setImageTexture("word_stage2.png");
			break;
		case 3:
			stages->setImageTexture("word_stage3.png");
			break;
		default:
			stages->setImageTexture("word_stage1.png");
			break;
		}
		MyGUI::ImageBox* result = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("result_of_play");
		result->setImageTexture("fail.png");
		mStagePass1->getGUI()->findWidget<MyGUI::Window>("ed_window")->setVisible(true);
		mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("next_one")->setImageTexture("nextStageUnuse.png");
		mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("next_one")->setEnabled(false);
	}

	// 游戏胜利
	else if (mStagePass1->isRunning() && monsterManager->isWinGame())
	{
		mStagePass1->setRunning(false);
		Sound::getInstance()->play("../Media/Sound/win.wav", false);
		MyGUI::ImageBox* stages = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("word_of_stages");
		switch(mStagePass1->getLevel())
		{
		case 1:
			stages->setImageTexture("word_stage1.png");
			break;
		case 2:
			stages->setImageTexture("word_stage2.png");
			break;
		case 3:
			stages->setImageTexture("word_stage3.png");
			break;
		default:
			stages->setImageTexture("word_stage1.png");
			break;
		}
		MyGUI::ImageBox* result = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("result_of_play");
		result->setImageTexture("sucess.png");
		mStagePass1->getGUI()->findWidget<MyGUI::Window>("ed_window")->setVisible(true);
	}

	else if (mStagePass1->isRunning())
	{
		BulletManager& bulletManager = mStagePass1->getBulletManager();
		Vector3 gravity = mStagePass1->getGravity();
		bulletManager.fly(timeSinceLastFrame, gravity);

		Maze* maze = mStagePass1->getMaze();
		std::vector<NameValueList> explodedBullets = bulletManager.getAndRemoveExplodedBullets(maze->getHorizon());
		monsterManager->updateState(
			explodedBullets,
			timeSinceLastFrame,
			SceneManagerContainer::getSceneManager()
			);
	}
	
		
	return true;
}

bool StagePass1Step1::onKeyPressed(const OIS::KeyEvent& arg)
{
	// 处于答题阶段时无法进行操作
	if (Questions::getInstance()->isAnswering()) return true;

	// 发炮
	if (arg.key == OIS::KC_SPACE)
	{
		Bullet* bullet = mStagePass1->getCannon()->fire(SceneManagerContainer::getSceneManager());
		if (bullet)
		{
			mStagePass1->getBulletManager().add(bullet);
			Sound::getInstance()->play("../Media/Sound/fire.wav", false);
			mStagePass1->updateCount();
		}
	}
	// 换炮弹
	else if (arg.key == OIS::KC_TAB)
	{
		Sound::getInstance()->play("../Media/Sound/switch.wav", false);
		mStagePass1->getCannon()->changeBullet();

		mStagePass1->updateImage(); 
		
	}
	else if (arg.key >= OIS::KC_1 && arg.key <= OIS::KC_9)
	{
		Sound::getInstance()->play("../Media/Sound/switch.wav", false);
		mStagePass1->getCannon()->changeBullet(arg.key - OIS::KC_1);
	}
	// 答题
	else if (arg.key == OIS::KC_Q)
		Questions::getInstance()->popUpQuestion();
	// test by kid
	else if (arg.key == OIS::KC_L)
		mStagePass1->getUFO()->setBlood(-1);
		
	return true;
}

bool StagePass1Step1::onMouseMoved(const OIS::MouseEvent& arg)
{
	// 处于答题阶段时无法进行操作
	if (Questions::getInstance()->isAnswering()) return true;

	//StagePass1->getCannon()->rotate(-arg.state.X.rel, arg.state.Y.rel);
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