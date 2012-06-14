#include "StagePass1Step1.h"


StagePass1Step1::StagePass1Step1(StagePass1* stagePass1)
	: mStagePass1(stagePass1)
{
}

void StagePass1Step1::init()
{
	
	mStagePass1->getCamera()->setPosition(Vector3(0, 1200, 2000));
	mStagePass1->getCamera()->setDirection(Vector3(0, -500, -1000));
}

bool StagePass1Step1::run(float timeSinceLastFrame)
{
	BulletManager& bulletManager = mStagePass1->getBulletManager();
	Vector3 gravity = mStagePass1->getGravity();
	bulletManager.fly(timeSinceLastFrame, gravity);

	MonsterManager* monsterManager = mStagePass1->getMonsterManager();
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
	// ·¢ÅÚ
	if (arg.key == OIS::KC_SPACE)
	{
		Bullet* bullet = mStagePass1->getCannon()->fire(SceneManagerContainer::getSceneManager());
		if (bullet)
			mStagePass1->getBulletManager().add(bullet);
	}
	// »»ÅÚµ¯
	else if (arg.key == OIS::KC_TAB)
		mStagePass1->getCannon()->changeBullet();
	else if (arg.key >= OIS::KC_1 && arg.key <= OIS::KC_9)
		mStagePass1->getCannon()->changeBullet(arg.key - OIS::KC_1);
		
	return true;
}

bool StagePass1Step1::onMouseMoved(const OIS::MouseEvent& arg)
{
	mStagePass1->getCannon()->rotate(-arg.state.X.rel, arg.state.Y.rel);
	
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