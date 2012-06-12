#include "Cell.h"

Cell::Cell(void)
{

}

Cell::Cell(Ogre::SceneManager* sceneManager,Ogre::SceneNode* parentNode,Ogre::Vector2* pos)
{
	this->mSceneManager = sceneManager;
	this->mParentNode = parentNode;
	this->mHarmValue = 0.0f;
	this->mType = FREE;
	this->mSceneNode = NULL;
	this->mEntity = NULL;
}

Cell::Cell( Ogre::SceneManager* sceneManager,Ogre::SceneNode* parentNode,Ogre::String mesh,Ogre::Vector2* pos, CellType type, float harmValue)
{
	this->mSceneManager = sceneManager;
	this->mParentNode = parentNode;
	this->mHarmValue = harmValue;
	this->mEntity = ObjectFactory::createEntity(sceneManager,mesh);
	float x = this->mEntity->getBoundingBox().getSize().x;
	float z = this->mEntity->getBoundingBox().getSize().z;
	this->mSceneNode = ObjectFactory::createSceneNode(parentNode,this->mEntity, Vector3(x * pos->x,Real(0), z * pos->y));
	this->mType = type;
}

Cell::Cell( Ogre::SceneManager* sceneManager,Ogre::SceneNode* parentNode,Ogre::String mesh,Ogre::Vector2* pos,int type, float harmValue)
{
	this->mSceneManager = sceneManager;
	this->mParentNode = parentNode;
	this->mHarmValue = harmValue;
	this->mEntity = ObjectFactory::createEntity(sceneManager,mesh);
	float x = this->mEntity->getBoundingBox().getSize().x;
	float z = this->mEntity->getBoundingBox().getSize().z;
	float y = this->mEntity->getBoundingBox().getSize().y;
	//float x = 100.0f;
	//float z = 100.0f;
	this->mSceneNode = ObjectFactory::createSceneNode(parentNode,this->mEntity, Vector3(x * pos->x,Real(0), z * pos->y));
	switch(type){
	case 0:
		this->mType = FREE;
		break;
	case 1:
		this->mType = WALL;
		break;
	case 2:
		this->mType = SPIKEWEED;
		break;
	case 3:
		this->mType = SWAMP;
		break;
	case 4:
		this->mType = TRAP;
		break;
	default:
		this->mType = FREE;
	}
}

Cell::~Cell(void)
{
}


CellType Cell::getCellType()
{
	return this->mType;
}

float Cell::getHeight()
{
	return this->mEntity->getBoundingBox().getSize().y;
}

float Cell::getHarmValue()
{
	return this->mHarmValue;
}

bool Cell::setCellType( CellType type, Ogre::String mesh, float harmValue )
{
	
	if(this->mSceneNode != NULL)
	{
		this->mSceneNode->detachAllObjects();
		this->mEntity = ObjectFactory::createEntity(mSceneManager,mesh);
		this->mSceneNode->attachObject(this->mEntity);
	}
	else
	{
		this->mEntity = ObjectFactory::createEntity(mSceneManager,mesh);
		float x = this->mEntity->getBoundingBox().getSize().x;
		float z = this->mEntity->getBoundingBox().getSize().z;
		this->mSceneNode = ObjectFactory::createSceneNode(mParentNode,this->mEntity, Vector3(x * this->pPos->x,Real(0), z * this->pPos->y));
		this->mSceneNode->attachObject(this->mEntity);
	}
	this->mType = type;
	this->mHarmValue = harmValue;
	return true;
}

bool Cell::setCellType( CellType type )
{
	if(this->mSceneNode != NULL)
	{
		this->mSceneNode->detachAllObjects();
	}
	this->mType = type;
	this->mHarmValue = 0.0f;
	return true;

}
