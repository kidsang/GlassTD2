#include "UFO.h"

#include "ObjectFactory.h"

UFO::UFO(Ogre::SceneNode* node, Ogre::Entity* entity, int blood)
	: mNode(node), mEntity(entity), mBlood(blood)
{
}


UFO::~UFO(void)
{
}