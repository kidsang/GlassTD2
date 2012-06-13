
#ifndef __UFO_h_
#define __UFO_h_

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class UFO
{
private:
	int mBlood;
	Ogre::SceneNode* mNode;
	Ogre::Entity* mEntity;
public:
	UFO(void);
	UFO(Ogre::SceneManager* manager, Ogre::SceneNode* parent, Ogre::String mesh, Ogre::Vector3 pos,int blood);
	~UFO(void);
	void setBlood(int blood);
	int getBlood();
	bool isDestroy();
};

#endif

