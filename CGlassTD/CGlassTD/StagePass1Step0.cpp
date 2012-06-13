#include "StagePass1Step0.h"
#include "SceneManagerContainer.h"
#include "CellType.h"
#include <OgreMath.h>
#include <sstream>


bool equal(Cell* firstCell, Cell* secondCell)
{
	return firstCell == secondCell;
}


StagePass1Step0::StagePass1Step0(StagePass1* stagePass1)
	: mStagePass1(stagePass1), mCurrentState(WITH_SWAMP), mCurrentCell(NULL)
{
	mRaySceneQuery = SceneManagerContainer::getSceneManager()->createRayQuery(Ogre::Ray());
}

StagePass1Step0::~StagePass1Step0()
{
	SceneManagerContainer::getSceneManager()->destroyQuery(mRaySceneQuery);
}

void StagePass1Step0::init()
{
	/// 改变镜头视角
	mStagePass1->getCamera()->setPosition(Vector3(0, 2000, 1000));
	mStagePass1->getCamera()->setDirection(-mStagePass1->getCamera()->getPosition());

	// debug text
	debugText = mStagePass1->getGUI()->createWidget<MyGUI::StaticText>("TextBox", 10, 40, 300, 300, MyGUI::Align::Default, "Main");
	debugText->setTextColour(MyGUI::Colour::White);
	debugText->setCaption("no");
}

void StagePass1Step0::run(float timeSinceLastFrame)
{
}

void StagePass1Step0::onKeyPressed(const OIS::KeyEvent& arg)
{
	// 按 G 结束布局阶段，开始打怪阶段
	if (arg.key == OIS::KC_G)
	{
		mStagePass1->jumpToStep(1);
	}
}


void StagePass1Step0::onMouseMoved(const OIS::MouseEvent& arg)
{
	if (mCurrentState == NOTHING) return;  // 用户并没有选中陷阱，也就是
	
	Ogre::Vector3 position;
	if (!this->convert(arg, position)) return;
	
	Maze* maze = mStagePass1->getMaze();
	Cell* cell = maze->getCellByPos(position);
	if (cell == NULL) return;

	std::ostringstream x;
	std::ostringstream y;
	std::ostringstream positionX;
	std::ostringstream positionY;
	std::ostringstream positionZ;
	std::ostringstream pcell;
	std::ostringstream poldcell;
	x << arg.state.X.abs;
	y << arg.state.Y.abs;
	positionX << position[0];
	positionY << position[1];
	positionZ << position[2];
	pcell << cell;
	poldcell << mCurrentCell;

	double xInput = position.x;
	xInput += 801;
	if( xInput < 0 ) xInput = 0;
	if( xInput > 1599 ) xInput = 1599;

	double zInput = position.z;
	zInput += 801;
	if( zInput < 0 ) zInput = 0;
	if( zInput > 1599 ) zInput = 1599;

	int xx = (int)xInput / 100;
	int yt = (int)zInput / 100;

	std::ostringstream xxx;
	std::ostringstream yyy;
	xxx << xx;
	yyy << yt;

	std::string display = x.str() + ' ' + y.str() + '\n';
	display += positionX.str() + ' ' + positionY.str() + ' ' + positionZ.str() + '\n';
	display += pcell.str() + ' ' + poldcell.str() + '\n';
	display += xxx.str() + ' ' + yyy.str() + '\n';

	debugText->setCaption(display.c_str());
	//debugText->setCaption("no");
	
	if (cell != mCurrentCell)
	{
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
}

void StagePass1Step0::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}

void StagePass1Step0::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
}

bool StagePass1Step0::convert(const OIS::MouseEvent& arg, Ogre::Vector3& output)
{
	float x = (float)arg.state.X.abs;
	float y = (float)arg.state.Y.abs;
	float width = (float)arg.state.width;
	float height = (float)arg.state.height;
	
	Ogre::Ray mouseRay = mStagePass1->getCamera()->getCameraToViewportRay(x/width, y/height);
	
	Vector3 normal = Vector3(0, 1, 0);
	Real distance = mStagePass1->getMaze()->getHorizon();
	
	Plane plane = Plane(normal, distance);
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
	
	/*
	mRaySceneQuery->setRay(mouseRay);
	
	Ogre::RaySceneQueryResult& result = mRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator itr = result.begin();
	if (itr != result.end())
	{
		if (itr->movable)
		{
			Entity* obj = (Entity*)itr->movable;
			output = obj->getParentNode()->_getDerivedPosition();
			return true;
		}
	}
	return false;*/
}