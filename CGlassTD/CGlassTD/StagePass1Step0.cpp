#include "StagePass1Step0.h"
#include "SceneManagerContainer.h"
#include "CellType.h"
#include "StagePass1Step1.h"
#include "Score.h"
#include "Money.h"
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
	/// �ı侵ͷ�ӽ�
	mStagePass1->getCamera()->setPosition(Vector3(0, 2000, 1000));
	mStagePass1->getCamera()->setDirection(-mStagePass1->getCamera()->getPosition());

	// debug text
	debugText = mStagePass1->getGUI()->createWidget<MyGUI::StaticText>("TextBox", 10, 40, 300, 300, MyGUI::Align::Default, "Main");
	debugText->setTextColour(MyGUI::Colour::White);
	debugText->setCaption("no");
}

bool StagePass1Step0::run(float timeSinceLastFrame)
{
	return true;
}

bool StagePass1Step0::onKeyPressed(const OIS::KeyEvent& arg)
{
	switch (arg.key)
	{
	// �� G �������ֽ׶Σ���ʼ��ֽ׶�
	case OIS::KC_G:
		mStagePass1->getMaze()->clearShadow();
		mStagePass1->jumpToStep(new StagePass1Step1(mStagePass1));
		break;
	// ��ʱ
	// �� A ���ش�, �� B ������ �� C �����޼�
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
	if (mCurrentState == NOTHING) return true;  // �û���û��ѡ��Ҫ���õ�����
	
	// ����Ļ����ת���ɳ����е���ά����
	Ogre::Vector3 position;
	if (!this->convert(arg, position)) return true;
	
	// ����ת����������ø�λ�õ�cell
	Maze* maze = mStagePass1->getMaze();
	Cell* cell = maze->getCellByPos(position);
	if (cell == NULL) return true;

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
	
	// �����cell���ϴ����õ�cell��ͬһ������������������������if
	if (cell != mCurrentCell)
	{
		// �õ�ͼ�ڸ�λ����ʾһ����Ӱ����¼�¸�λ�ã��������ϴε���Ӱ
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
		// ...���������Ӱʧ�ܣ�����λ�ò��ܷ������壬��������������������if����ɼ�¼�ͳ���
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
	
	return true;
}

bool StagePass1Step0::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (id != OIS::MB_Left) return true;  // ��ʱ��ֻ������Ż���Ч
	if (mCurrentState == NOTHING) return true;  // �û�û��ѡ���κ�����

	Ogre::Vector3 position;
	if (!this->convert(arg, position)) return true;
	
	Money* money = Money::getInstance();
	
	Maze* maze = mStagePass1->getMaze();
	switch (mCurrentState)
	{
	case WITH_SWAMP:
		if (money->placeTrap(Money::TrapType::SWAMP))
		{
			maze->editMaze(position, SWAMP);
		}
		break;
	case WITH_SPIKEWEED:
		if (money->placeTrap(Money::TrapType::SPIKEWEED))
		{
			maze->editMaze(position, SPIKEWEED);
		}
		break;
	case WITH_TRAP:
		if (money->placeTrap(Money::TrapType::TRAP))
		{
			maze->editMaze(position, TRAP);
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
	
	// ��ô������������һ������
	Ogre::Ray mouseRay = mStagePass1->getCamera()->getCameraToViewportRay(x/width, y/height);
	
	// �����Թ��ĵذ�߶�����һ��ƽ��
	Vector3 normal = Vector3(0, 1, 0);
	Real distance = mStagePass1->getMaze()->getHorizon();
	Plane plane = Plane(normal, distance);

	// ������ߺ�ƽ��Ľ���
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