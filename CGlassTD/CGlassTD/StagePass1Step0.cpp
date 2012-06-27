#include "StagePass1Step0.h"
#include "SceneManagerContainer.h"
#include "CellType.h"
#include "StagePass1Step1.h"
#include "Score.h"
#include "Money.h"
#include <OgreMath.h>
#include <sstream>
#include "CameraStep02Step1Animator.h"
#include <MyGUI/MyGUI.h>

bool equal(Cell* firstCell, Cell* secondCell)
{
	return firstCell == secondCell;
}


StagePass1Step0::StagePass1Step0(LevelStage* stagePass1)
	: mStagePass1(stagePass1), mCurrentState(WITH_SWAMP), mCurrentCell(NULL),
	mRollX(0), mRollY(0)
{
	mRaySceneQuery = SceneManagerContainer::getSceneManager()->createRayQuery(Ogre::Ray());

	this->mStagePass1->createGUI0();
	setNotify();
}

StagePass1Step0::~StagePass1Step0()
{
	SceneManagerContainer::getSceneManager()->destroyQuery(mRaySceneQuery);
}

void StagePass1Step0::init()
{
	/// 改变镜头视角
	mStagePass1->getCamera()->setPosition(Vector3(0, 2000, 1000));
	mStagePass1->getCamera()->lookAt(Vector3(0, 0, 0));
}

bool StagePass1Step0::run(float timeSinceLastFrame)
{
	// 卷动画面
#ifdef _DEBUG
	const int moveStep = 60;
#else
	const int moveStep = 5;
#endif
	mStagePass1->getCamera()->move(Ogre::Vector3(moveStep * mRollX, 0, moveStep * mRollY));

	// 限制照相机在某个范围内
	// 丑陋的代码by kid
	Vector3 campos = mStagePass1->getCamera()->getPosition();
	const int xlimit = 1000;
	const int zlimit = 1100;
	if (campos.x < -xlimit) campos.x = -xlimit;
	else if (campos.x > xlimit) campos.x = xlimit;
	if (campos.z < zlimit * .2f) campos.z = zlimit * .2f;
	else if (campos.z > zlimit) campos.z = zlimit;
	mStagePass1->getCamera()->setPosition(campos);

	return true;
}

bool StagePass1Step0::onKeyPressed(const OIS::KeyEvent& arg)
{
	switch (arg.key)
	{
	// 按 G 结束布局阶段，开始打怪阶段
	case OIS::KC_G:
		{
			MyGUI::PointerManager::getInstance().setVisible(false);
			// 丑陋的代码by kid
#ifdef _DEBUG
			CameraStep02Step1Animator* ani = new CameraStep02Step1Animator(0);
#else
			CameraStep02Step1Animator* ani = new CameraStep02Step1Animator(0.02f);
#endif
			ani->start(mStagePass1->getCamera());
			mStagePass1->addCameraAnimator(ani);
			//mStagePass1->jumpToStep(new StagePass1Step1(mStagePass1));
			mStagePass1->change0to1();
		}
		break;
	// 暂时
	// 按 A 键地刺, 按 B 键沼泽， 按 C 键捕兽夹
	case OIS::KC_A:
		mCurrentState = WITH_SPIKEWEED;
		break;
	case OIS::KC_B:
		mCurrentState = WITH_SWAMP;
		break;
	case OIS::KC_C:
		mCurrentState = WITH_TRAP;
		break;
	}
	
	return true;
}


bool StagePass1Step0::onMouseMoved(const OIS::MouseEvent& arg)
{
	if (mCurrentState == NOTHING) return true;  // 用户并没有选中要布置的陷阱
	
	// 将屏幕坐标转换成场景中的三维坐标
	Ogre::Vector3 position;
	if (!this->convert(arg, position)) return true;
	
	// 根据转换后的坐标获得该位置的cell
	Maze* maze = mStagePass1->getMaze();
	Cell* cell = maze->getCellByPos(position);
	if (cell == NULL) return true;
	
	// 如果该cell与上次设置的cell是同一个，则不作处理，否则进入下面的if
	if (cell != mCurrentCell)
	{
		// 让地图在该位置显示一个虚影，记录下该位置，并撤销上次的虚影
		bool result = false;
		switch (mCurrentState)
		{
		case WITH_SWAMP:
			result = maze->editMaze(position, SHADOW_SWAMP);
			break;
		case WITH_SPIKEWEED:
			result = maze->editMaze(position, SHADOW_SPIKEWEED);
			break;
		case WITH_TRAP:
			result = maze->editMaze(position, SHADOW_TRAP);
			break;
		} 
		// ...如果设置虚影失败，即该位置不能放置陷阱，则不作处理，否则进入下面的if，完成记录和撤销
		if (result)
		{
			if (mCurrentCell != NULL)
			{
				maze->editMaze(mLastPos, FREE);
			}
			
			mCurrentCell = cell;
			mLastPos = position;
		}
	}

	// 鼠标卷动画面
	int width = MyGUI::RenderManager::getInstance().getViewSize().width;
	int height = MyGUI::RenderManager::getInstance().getViewSize().height;
	if (arg.state.X.abs <= 16)
		mRollX = -1;
	else if (arg.state.X.abs >= width - 16)
		mRollX = 1;
	else
		mRollX = 0;
	if (arg.state.Y.abs <= 16)
		mRollY = -1;
	else if (arg.state.Y.abs >= height - 16)
		mRollY = 1;
	else
		mRollY = 0;
	
	return true;
}

bool StagePass1Step0::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (id != OIS::MB_Left) return true;  // 暂时让只有左键才会生效
	if (mCurrentState == NOTHING) return true;  // 用户没有选中任何陷阱

	Ogre::Vector3 position;
	if (!this->convert(arg, position)) return true;
	
	Money* money = Money::getInstance();
	
	Maze* maze = mStagePass1->getMaze();
	switch (mCurrentState)
	{
	case WITH_SWAMP:
		if (money->enough(Money::SWAMP))
		{
			if (maze->editMaze(position, SWAMP))
			{
				money->placeTrap(Money::SWAMP);
			}
		}
		break;
	case WITH_SPIKEWEED:
		if (money->enough(Money::SPIKEWEED))
		{
			if (maze->editMaze(position, SPIKEWEED))
			{
				money->placeTrap(Money::SPIKEWEED);
			}
		}
		break;
	case WITH_TRAP:
		if (money->enough(Money::TRAP))
		{
			if (maze->editMaze(position, TRAP))
			{
				money->placeTrap(Money::TRAP);
			}
		}
		break;
	}
	
	return true;
}

bool StagePass1Step0::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool StagePass1Step0::convert(const OIS::MouseEvent& arg, Ogre::Vector3& output)
{
	float x = (float)arg.state.X.abs;
	float y = (float)arg.state.Y.abs;
	float width = (float)arg.state.width;
	float height = (float)arg.state.height;
	
	// 获得从摄像机到鼠标的一条射线
	Ogre::Ray mouseRay = mStagePass1->getCamera()->getCameraToViewportRay(x/width, y/height);
	
	// 根据迷宫的地板高度生成一个平面
	Vector3 normal = Vector3(0, 1, 0);
	Real distance = mStagePass1->getMaze()->getHorizon();
	Plane plane = Plane(normal, distance);

	// 求出射线和平面的交点
	std::pair<bool, Real> result = Math::intersects(mouseRay, plane);
	if (result.first == true)
	{
		output = mouseRay.getOrigin() + mouseRay.getDirection() * result.second;
		return true;
	}
	else
	{
		return false;
	}
}


void StagePass1Step0::setNotify()
{
	this->mStagePass1->cellImage[0]->eventMouseButtonPressed += MyGUI::newDelegate(this, &StagePass1Step0::guiNotifyMousePressSwamp);
	this->mStagePass1->cellImage[1]->eventMouseButtonPressed += MyGUI::newDelegate(this, &StagePass1Step0::guiNotifyMousePressSpikeweed);
	this->mStagePass1->cellImage[2]->eventMouseButtonPressed += MyGUI::newDelegate(this, &StagePass1Step0::guiNotifyMousePressTrap);
	this->mStagePass1->cellImage[0]->eventMouseButtonReleased += MyGUI::newDelegate(this, &StagePass1Step0::guiNotifyMouseReleaseSwamp);
	this->mStagePass1->cellImage[1]->eventMouseButtonReleased += MyGUI::newDelegate(this, &StagePass1Step0::guiNotifyMouseReleaseSpikeweed);
	this->mStagePass1->cellImage[2]->eventMouseButtonReleased += MyGUI::newDelegate(this, &StagePass1Step0::guiNotifyMouseReleaseTrap);
}
void StagePass1Step0::guiNotifyMousePressSwamp(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	mCurrentState = WITH_SWAMP;
	_sender->castType<MyGUI::ImageBox>()->setImageTexture("swamp_p.png");
}
void StagePass1Step0::guiNotifyMousePressSpikeweed(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	mCurrentState = WITH_SPIKEWEED;
	_sender->castType<MyGUI::ImageBox>()->setImageTexture("spikeweed_p.png");
}
void StagePass1Step0::guiNotifyMousePressTrap(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	mCurrentState = WITH_TRAP;
	_sender->castType<MyGUI::ImageBox>()->setImageTexture("trap_p.png");
}
void StagePass1Step0::guiNotifyMouseReleaseSwamp(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	_sender->castType<MyGUI::ImageBox>()->setImageTexture("swamp.png");
}
void StagePass1Step0::guiNotifyMouseReleaseSpikeweed(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	_sender->castType<MyGUI::ImageBox>()->setImageTexture("spikeweed.png");
}
void StagePass1Step0::guiNotifyMouseReleaseTrap(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	_sender->castType<MyGUI::ImageBox>()->setImageTexture("trap.png");
}