#include "Maze.h"
#include "Cell.h"
#include "ParamParser.h"
Maze::Maze(void)
{
}

Maze::Maze(SceneManager* sceneManager, int* map, int width, int height, Ogre::Vector3 start1, Ogre::Vector3 start2, Ogre::Vector3 final)
	: mWidth(width), mHeight(height), mSceneManager(sceneManager), 
	mMap(0)
{	
	ParamParser cellParser = ParamParser("CellDefine.xml");
	cellParser.parse();
	cellParser.moveToFirst();
	NameValueList* cellParams = cellParser.getNext();
	this->mWall = (*cellParams)["wall"];
	this->mSwamp = (*cellParams)["swamp"];
	this->mSpikeweed = (*cellParams)["spikeweed"];
	this->mTrap = (*cellParams)["trap"];
	this->mShadowSwamp = (*cellParams)["shadowSwamp"];
	this->mShadowSpikeweed = (*cellParams)["shadowSpikeweed"];
	this->mShadowTrap = (*cellParams)["shadowTrap"];
	cellParams = cellParser.getNext();
	this->mCellWidth = (int)(atoi((*cellParams)["width"].c_str()));	
	this->mCellHeight = (int)(atoi((*cellParams)["width"].c_str()));	
	this->mCellLength = (int)(atoi((*cellParams)["width"].c_str()));	
	cellParams = cellParser.getNext();
	this->mHarmSpikeweed = (float)(atof((*cellParams)["spikeweed"].c_str()));	
	this->mHarmSwamp = (float)(atof((*cellParams)["swamp"].c_str()));	


	this->mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("mapSenenNode");
	this->pZones = new Cell[mWidth * mHeight];
	this->pMapInfo = new int[mWidth * mHeight];
	this->startPos = std::vector<Ogre::Vector3>();
	this->mSceneNode->setPosition(Ogre::Vector3(-mWidth / 2.0f * this->mCellWidth, 0, -mHeight / 2.0f * this->mCellHeight));

	for(int j = 0; j < width; ++j)
	{
		for(int i = 0; i < height; ++i)
		{
			switch(map[j * width + i])
			{
			case 0:
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode, new Ogre::Vector2(Real(i),Real(j)));
				break;
			case 1:
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode,this->mWall, new Ogre::Vector2(Real(i),Real(j)), map[j * width + i], 0.0f );
				break;
			case 2:
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode,this->mSpikeweed, new Ogre::Vector2(Real(i),Real(j)), map[j * width + i], this->mHarmSpikeweed );
				break;
			case 3:
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode,this->mSwamp, new Ogre::Vector2(Real(i),Real(j)), map[j * width + i],this->mHarmSwamp );
				break;
			case 4:
				this->pZones[j * width + i] = Cell(sceneManager, mSceneNode,this->mTrap, new Ogre::Vector2(Real(i),Real(j)), map[j * width + i], 0.0f );
				break;
			}
		}
	}
	this->horizon = this->mCellLength / 2.0f; 
	this->startPos.clear();
	this->startPos.push_back(start1);
	this->startPos.push_back(start2);
	this->finalPos = final; 
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
	/// 将世界坐标转换成地图坐标，注意边界部分越界
	/*int x = ((int)pos.x / 100);
	if(x < 0)
	{
		x += (mWidth / 2 - 1);
	}
	else 
		x += (mWidth / 2);

	int y = (int)pos.z / 100;
	if(y < 0)
	{
		y += (mHeight / 2 - 1);
	}
	else 
		y += (mHeight / 2);
	if(y < 0 || y >= mHeight || x < 0 || x >= mWidth)
	{
		return NULL;
	}*/

	double xInput = pos.x;
	xInput += 801;
	if( xInput < 0 ) xInput = 0;
	if( xInput > 1599 ) xInput = 1599;

	double zInput = pos.z;
	zInput += 801;
	if( zInput < 0 ) zInput = 0;
	if( zInput > 1599 ) zInput = 1599;

	int x = (int)xInput / 100;
	int y = (int)zInput / 100;

	return &this->pZones[y * mHeight + x];
}


bool Maze::editMaze( Ogre::Vector3 pos, CellType type )
{
	Cell* cell = this->getCellByPos(pos);
	if(cell->getCellType() == WALL || 
		cell->getCellType() == TRAP ||
		cell->getCellType() == SWAMP ||
		cell->getCellType() == SPIKEWEED)
	{
		return false;
	}
	switch(type)
	{
	case FREE:
		return cell->setCellType(type);
		break;
	case TRAP:
		return cell->setCellType(type,this->mTrap,0.0f);
		break;
	case WALL:
		return cell->setCellType(type,this->mWall, 0.0f);
		break;
	case SWAMP:
		return cell->setCellType(type,this->mSwamp, this->mHarmSwamp);
		break;
	case SPIKEWEED:
		return cell->setCellType(type,this->mSpikeweed, this->mHarmSpikeweed);
		break;
	case SHADOW_SPIKEWEED:
		return cell->setCellType(type,this->mShadowSpikeweed, 0.0f);
		break;
	case SHADOW_SWAMP:
		return cell->setCellType(type,this->mShadowSwamp, 0.0f);
		break;
	case SHADOW_TRAP:
		return cell->setCellType(type,this->mShadowTrap,0.0f);
		break;
	default:
		return false;
	}
}


Ogre::Vector3 Maze::getFinalPos()
{
	return this->finalPos;
}

int Maze::getEntityHeight()
{
	return this->mCellHeight;
}

int Maze::getEntityWidth()
{
	return this->mCellWidth;
}



