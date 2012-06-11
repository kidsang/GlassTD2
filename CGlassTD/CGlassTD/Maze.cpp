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
	/// ˵���������ģ�ʹ�С������������������������100��ģ�͵ĳ��͸ߣ�������һ���ģ�ʵ�����ǿ��Բ�һ���ġ���������������
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
				/// ˵�������ڻ�û��ģ�ͳ����������е����嶼��ǽ����ʾ��������ע���ˣ�����������
				/// ���ﻹҪ������ģ�͵����֣���ʱ����cubess.mesh�ˣ�������������
				/// �����˺�ֵҲҪ��������������˺�ֵ��һ���ģ������ˣ���λ:w
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode,"cubess.mesh", new Ogre::Vector2(Real(i),Real(j)), map[j * width + i], 0.1f );
			}
		}
	}
	this->horizon = this->pZones[1].getHeight() / 2.0f;
	this->startPos.clear();
	/// ����ҲҪ������������������ʼ��������������,����������һ����ͨ����xml�ļ���д��
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
	/// ���������
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


