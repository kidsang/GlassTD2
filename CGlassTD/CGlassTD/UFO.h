
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
	UFO(Ogre::SceneNode* node, Ogre::Entity* entity, int blood);
	~UFO(void);

	void setBlood(int blood)
	{
		mBlood = blood;
	}

	int getBlood()
	{
		return mBlood;
	}

	bool isDestroy()
	{
		return (mBlood <= 0);
	}
};

#endif

