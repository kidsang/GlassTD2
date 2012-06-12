#include "StagePass1Step0.h"
#include "SceneManagerContainer.h"
#include "CellType.h"


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
	if (mCurrentState == NOTHING) return;
	
	Ogre::Vector3 position;
	if (!this->convert(arg, position)) return;
	
	Maze* maze = mStagePass1->getMaze();
	Cell* cell = maze->getCellByPos(position);
	if (cell == NULL) return;
	
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
	mRaySceneQuery->setRay(mouseRay);
	
	Ogre::RaySceneQueryResult& result = mRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator itr = result.begin();
	if (itr != result.end())
	{
		if (itr->movable)
		{
			MovableObject* obj = itr->movable;
			output = obj->getParentNode()->getPosition();
			return true;
		}
	}
	return false;
}