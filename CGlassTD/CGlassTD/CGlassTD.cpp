#include "CGlassTD.h"
#include "StagePass1.h"
#include "Questions.h"
#include "StartStage.h"
#include "StageSelect.h"
#include "cutScenes.h"
#include "Money.h"

//-------------------------------------------------------------------------------------
CGlassTD::CGlassTD(void)
{
}
//-------------------------------------------------------------------------------------
CGlassTD::~CGlassTD(void)
{
	if (mpStageManager != NULL)
	{
		delete mpStageManager;
	}
}

//------------------------------------------------------
void CGlassTD::chooseSceneManager(void)
{
	BaseApplication::chooseSceneManager();

	SceneManagerContainer::setup(mSceneMgr);
}

//-------------------------------------------------------------------------------------
void CGlassTD::createScene(void)
{
	// MyGui
	mGuiPlatform = new MyGUI::OgrePlatform();
	mGuiPlatform->initialise(mWindow, mSceneMgr);
	mGui = new MyGUI::Gui();
	mGui->initialise();
	
	Questions::init(mGui);
	Money::init(mGui);

	// 全屏幕泛光
	Ogre::Camera* camera = mSceneMgr->getCamera("PlayerCam");
	Ogre::CompositorManager::getSingleton().addCompositor(camera->getViewport(), "Bloom");
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(camera->getViewport(), "Bloom", true);

	// 粒子系统
    //Ogre::ParticleSystem* ps = mSceneMgr->createParticleSystem("Fireworks", "Examples/GreenyNimbus");
	//mSceneMgr->getRootSceneNode()->attachObject(ps);

	// test gui
	//MyGUI::ButtonPtr button = mGui->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	//button->setCaption("exit");

	// 创建场景
	mpStageManager = new StageManager(mSceneMgr);
	mpStageManager->setStage(new StagePass1(mSceneMgr, mpStageManager, mGui));
	//mpStageManager->setStage(new StartStage(mSceneMgr, mpStageManager, mGui)); 
	//mpStageManager->setStage(new StageSelect(mSceneMgr, mpStageManager, mGui)); 
	//mpStageManager->setStage(new cutScenes(mSceneMgr, mpStageManager, mGui, 1));
}

bool CGlassTD::frameRenderingQueued( const Ogre::FrameEvent& evt )
{
	//
	if (!BaseApplication::frameRenderingQueued(evt))
		return false;

	// 运行当前场景的逻辑
	return mpStageManager->getStage()->run(evt.timeSinceLastFrame);
}

bool CGlassTD::keyPressed(const OIS::KeyEvent &arg)
{
	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
	return mpStageManager->getStage()->onKeyPressed(arg);
}

bool CGlassTD::keyReleased( const OIS::KeyEvent &arg )
{
	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
	return mpStageManager->getStage()->onKeyReleased(arg);
}

bool CGlassTD::mouseMoved(const OIS::MouseEvent &arg)
{
	MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
	return mpStageManager->getStage()->onMouseMoved(arg);
}

bool CGlassTD::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	return mpStageManager->getStage()->onMousePressed(arg, id);
}

bool CGlassTD::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	return mpStageManager->getStage()->onMouseReleased(arg, id);
}



#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
	// Create application object
	CGlassTD app;

	try {
		app.go();
	} catch( Ogre::Exception& e ) {
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}
