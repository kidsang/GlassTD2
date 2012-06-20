#include "StagePass1Step1.h"
#include "Questions.h"

#include "Sound.h"


StagePass1Step1::StagePass1Step1(LevelStage* stagePass1)
	: mStagePass1(stagePass1)
{
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
		MyGUI::PointerManager::getInstance().show();
		mStagePass1->setRunning(false);
		Sound::getInstance()->play("../Media/Sound/lose.wav", false);
		mStagePass1->getGUI()->findWidget<MyGUI::Window>("ed_window")->setVisible(true);
		mStagePass1->getGUI()->findWidget<MyGUI::Button>("ed_next_btn")->setVisible(false);
	}

	// 游戏胜利
	if (mStagePass1->isRunning() && monsterManager->isWinGame())
	{
		MyGUI::PointerManager::getInstance().show();
		mStagePass1->setRunning(false);
		Sound::getInstance()->play("../Media/Sound/win.wav", false);
		mStagePass1->getGUI()->findWidget<MyGUI::Window>("ed_window")->setVisible(true);
	}

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
		}
	}
	// 换炮弹
	else if (arg.key == OIS::KC_TAB)
	{
		Sound::getInstance()->play("../Media/Sound/switch.wav", false);
		mStagePass1->getCannon()->changeBullet();
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