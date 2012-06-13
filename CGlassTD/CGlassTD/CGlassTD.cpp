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
	/*MonsterManager* monsterMgr = MonsterManager::getMonsterManager();
	monsterMgr->monsterGenerate(mSceneMgr);*/
 /*   Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);
	*/

	//mpStageManager = new StageManager(mSceneMgr);
	mpStageManager = new StageManager(mSceneMgr);
	//mpStageManager->setStage(new TestStage(mSceneMgr, mpStageManager));
	mpStageManager->setStage(new StagePass1(mSceneMgr, mpStageManager));

	// MyGui
	mGuiPlatform = new MyGUI::OgrePlatform();
	mGuiPlatform->initialise(mWindow, mSceneMgr);
	mGui = new MyGUI::Gui();
	mGui->initialise();

	/*MyGUI::ButtonPtr button = mGui->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	button->setCaption("exit");*/
	MyGUI::LayoutManager::getInstance().loadLayout("my.layout");
	//MyGUI::ButtonPtr button = mGui->findWidget<MyGUI::Button>("MyFirstButton");
	
	//// 测试by kid
	// 测试by kid
	//BulletFactory* bf;
	//BulletFactory* bf;
	//bf = new TestBulletFactory();
	//bf = new TestBulletFactory();
	//mBulletFactoryMap.insert(std::make_pair(bf->getType(), bf));
	//mBulletFactoryMap.insert(std::make_pair(bf->getType(), bf));


}

bool CGlassTD::frameRenderingQueued( const Ogre::FrameEvent& evt )
{
	//
	BaseApplication::frameRenderingQueued(evt);

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
