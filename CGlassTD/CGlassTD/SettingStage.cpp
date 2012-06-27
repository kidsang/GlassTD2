#include "SettingStage.h"
#include "StartStage.h"
#include "Stage.h"

SettingStage::SettingStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	musicFlag = Stage::getMusicFlag();
	soundFlag = Stage::getSoundFlag();
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("setting.layout");
	sound = this->getGUI()->findWidget<MyGUI::ImageBox>("yinxiao");
	music = this->getGUI()->findWidget<MyGUI::ImageBox>("yinyue"); 
	back = this->getGUI()->findWidget<MyGUI::ImageBox>("back"); 
	if(musicFlag)
	{
		music->setImageTexture("settingSelect.png");
	}
	else
	{
		music->setImageTexture("settingNoSelect.png");
	}
	if(soundFlag)
	{
		sound->setImageTexture("settingSelect.png");
	}
	else
	{
		sound->setImageTexture("settingNoSelect.png");
	}
	
	sound->eventMouseButtonClick += MyGUI::newDelegate(this, &SettingStage::notifyMouseButtonClick);
	music->eventMouseButtonClick += MyGUI::newDelegate(this, &SettingStage::notifyMouseButtonClick);
	back->eventMouseButtonClick += MyGUI::newDelegate(this, &SettingStage::notifyMouseButtonClick);
}


SettingStage::~SettingStage(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

void SettingStage::notifyMouseButtonClick( MyGUI::Widget* _sender )
{
	if(_sender == sound)
	{
		if(!soundFlag)
		{
			sound->setImageTexture("settingSelect.png");
		}
		else
		{
			sound->setImageTexture("settingNoSelect.png");
		}
		soundFlag = !soundFlag;
		Stage::setSoundFlag(soundFlag);

	}
	else if(_sender == music)
	{
		if(!musicFlag)
		{

			music->setImageTexture("settingSelect.png");
		}
		else
		{
			music->setImageTexture("settingNoSelect.png");
		}
		musicFlag = !musicFlag;
		Stage::setMusicFlag(musicFlag);
	}
	else if(_sender == back)
	{
		Stage* nextStage = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
}

bool SettingStage::run( float timeSinceLastFrame )
{
	return true;
}

bool SettingStage::onKeyPressed( const OIS::KeyEvent &arg )
{
	return true;
}

bool SettingStage::onMouseMoved( const OIS::MouseEvent &arg )
{
	return true;
}

bool SettingStage::onMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

bool SettingStage::onMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}
