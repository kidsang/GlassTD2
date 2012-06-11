#include "Maze.h"
#include "Cell.h"

Maze::Maze(void)
{
}

Maze::Maze(SceneManager* sceneManager, int* map, int width, int height)
	: mWidth(width), mHeight(height), mSceneManager(sceneManager), 
	mMap(0)
{	
	this->mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("mapSenenNode");
	this->pZones = new Cell[mWidth * mHeight];
	this->pMapInfo = new int[mWidth * mHeight];
	this->startPos = std::vector<Ogre::Vector3>();
	/// 说明，这里的模型大小参数化，，，，，，，，即100是模型的长和高，这里是一样的，实际上是可以不一样的。。。。。。。。
	this->mSceneNode->setPosition(Ogre::Vector3(-mWidth / 2.0f * 100, 0, -mHeight / 2.0f * 100));

	for(int j = 0; j < width; ++j)
	{
		for(int i = 0; i < height; ++i)
		{
			if(map[j * width + i] == 0)
			{
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode, new Ogre::Vector2(Real(i),Real(j)));
			}
			else
			{
				/// 说明，由于还没有模型出来，故所有的陷阱都用墙来表示，，，，注意了，，，，，，
				/// 这里还要参数化模型的名字，暂时就用cubess.mesh了，，，，，，，
				/// 由于伤害值也要参数化，这里的伤害值是一样的，留意了，各位:w
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode,"cubess.mesh", new Ogre::Vector2(Real(i),Real(j)), map[j * width + i], 0.1f );
			}
		}
	}
	this->horizon = this->pZones[1].getHeight() / 2.0f;
	this->startPos.clear();
	/// 这里也要参数化，，，，即开始坐标是有两个的,结束坐标有一个，通过读xml文件来写入
	this->startPos.push_back(Ogre::Vector3(Real(0), Real(0), Real(12)));
	this->startPos.push_back(Ogre::Vector3(Real(0), Real(0), Real(4)));
	this->finalPos = Ogre::Vector3(15,0,8);
}


Maze::~Maze(void)
{
	delete this->pMapInfo;
}

Cell* Maze::getMazeInfo()
{
	return this->pZones;
}

float Maze::getHorizon()
{
	return this->horizon;
}

std::vector<Ogre::Vector3> Maze::getStartPos()
{
	return this->startPos;
}

int Maze::getMapWidth()
{
	return this->mWidth;
}

int Maze::getMapHeight()
{
	return this->mHeight;

}

Ogre::Vector3 Maze::translatePos( Ogre::Vector3 pos )
{
	return  Ogre::Vector3(Real((pos.x - (int)(this->mHeight / 2.0f)) * 100),Real(pos.y),Real((pos.z - (int)(this->mWidth / 2.0f)) * 100));
}

void Maze::addStartPos( Ogre::Vector3 pos )
{
	this->startPos.push_back(pos);
}

void Maze::setFinalPos( Ogre::Vector3 pos )
{
	this->finalPos = pos;
}

Cell* Maze::getCellByPos( Ogre::Vector3 pos )
{
	int x = (int)pos.x / this->mWidth;
	int y = (int)pos.y / this->mHeight;
	return &this->pZones[y * mHeight + x];
}


bool Maze::editMaze( Ogre::Vector3 pos, CellType type )
{
	Cell* cell = this->getCellByPos(pos);
	/// 参数化标记
	return cell->setCellType(type,"cubess.mesh",0.1f);
}


Ogre::Vector3 Maze::getFinalPos()
{
	return this->finalPos;
}

int Maze::getEntityHeight()
{
	return 100;
}

int Maze::getEntityWidth()
{
	return 100;
}


