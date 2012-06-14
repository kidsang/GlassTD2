#include "CGlassTD.h"
#include "StagePass1.h"


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

	// test gui
	MyGUI::ButtonPtr button = mGui->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	button->setCaption("exit");

	// 创建场景
	mpStageManager = new StageManager(mSceneMgr);
	mpStageManager->setStage(new StagePass1(mSceneMgr, mpStageManager, mGui));
}

bool CGlassTD::frameRenderingQueued( const Ogre::FrameEvent& evt )
{
	//
	if (!BaseApplication::frameRenderingQueued(evt))
		return false;

	// 运行当前场景的逻辑
	mpStageManager->getStage()->run(evt.timeSinceLastFrame);

	return true;
}

bool CGlassTD::keyPressed(const OIS::KeyEvent &arg)
{
	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
	mpStageManager->getStage()->onKeyPressed(arg);
	return true;
}

bool CGlassTD::mouseMoved(const OIS::MouseEvent &arg)
{
	MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
	mpStageManager->getStage()->onMouseMoved(arg);
	return true;
}

bool CGlassTD::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	mpStageManager->getStage()->onMousePressed(arg, id);
	return true;
}

bool CGlassTD::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	mpStageManager->getStage()->onMouseReleased(arg, id);
	return true;
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
