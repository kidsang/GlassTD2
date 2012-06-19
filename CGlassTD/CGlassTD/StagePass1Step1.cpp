#include "StagePass1Step1.h"


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
		{
			mStagePass1->getBulletManager().add(bullet);


			const int imageCount = 3;
			MyGUI::TextBox* bulletCount[imageCount];
			bulletCount[0] = mStagePass1->getGUI()->findWidget<MyGUI::TextBox>("b3");
			bulletCount[1] = mStagePass1->getGUI()->findWidget<MyGUI::TextBox>("b2");
			bulletCount[2] = mStagePass1->getGUI()->findWidget<MyGUI::TextBox>("b1");

			for(int i = 0; i < 3; i++)
			{
				std::ostringstream temp;
				temp << mStagePass1->getCannon()->getBulletFactories().at(i)->getAmmoCount();
				bulletCount[i]->setCaption(temp.str());
			}
		}
	}
	// »»ÅÚµ¯
	else if (arg.key == OIS::KC_TAB)
	{
		mStagePass1->getCannon()->changeBullet();

		const int imageCount = 3; 
		int imageSize = 40;

		MyGUI::ImageBox* image[imageCount];

		image[0] = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("bomb_red");
		image[1] = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("bomb_blue");
		image[2] = mStagePass1->getGUI()->findWidget<MyGUI::ImageBox>("bomb_black");

		int Big = image[0]->getWidth()>image[1]->getWidth()?0:1;
		Big = image[Big]->getWidth()>image[2]->getWidth()?Big:2;
		int Next = (Big+1)%3;
		int left = image[0]->getCoord().left;
		int top = image[Big]->getCoord().top;

		int flag[imageCount] = {0,0,0};
		flag[Big] = 1;
		flag[Next] = -1;
		image[0]->setCoord(left,image[0]->getCoord().top+flag[0]*imageSize, (image[0]->getWidth()-flag[0]*imageSize), (image[0]->getHeight()-flag[0]*imageSize));
		image[1]->setCoord(image[0]->getCoord().left+image[0]->getWidth(),image[1]->getCoord().top+flag[1]*imageSize, (image[1]->getWidth()-flag[1]*imageSize), (image[1]->getHeight()-flag[1]*imageSize));
		image[2]->setCoord(image[1]->getCoord().left+image[1]->getWidth(),image[2]->getCoord().top+flag[2]*imageSize, (image[2]->getWidth()-flag[2]*imageSize), (image[2]->getHeight()-flag[2]*imageSize));

	}
	else if (arg.key >= OIS::KC_1 && arg.key <= OIS::KC_9)
		mStagePass1->getCannon()->changeBullet(arg.key - OIS::KC_1);
		
	return true;
}

bool StagePass1Step1::onMouseMoved(const OIS::MouseEvent& arg)
{
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