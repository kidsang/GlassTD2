#include "UFO.h"

#include "ObjectFactory.h"

UFO::UFO(void)
{
}

UFO::UFO( Ogre::SceneManager* manager, Ogre::SceneNode* parent, Ogre::String mesh, Ogre::Vector3 pos,int blood)
{
	this->mEntity = ObjectFactory::createEntity(manager,mesh);
	this->mNode = ObjectFactory::createSceneNode(parent,this->mEntity, pos);
	this->mBlood = blood;
}


UFO::~UFO(void)
{
}

void UFO::setBlood( int blood )
{
	mBlood = blood;
}

int UFO::getBlood()
{
	return mBlood;
}

bool UFO::isDestroy()
{
	if(mBlood <= 0)
	{
		return true;
	}
	return false;
}
