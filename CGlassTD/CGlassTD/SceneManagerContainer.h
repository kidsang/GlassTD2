#ifndef __SceneManagerContainer_h_
#define __SceneManagerContainer_h_

#include <OgreSceneManager.h>

/// µ¥ÀıÄ£Ê½
class SceneManagerContainer
{
private:
	SceneManagerContainer();
	SceneManagerContainer(SceneManagerContainer&);

public:
	static void setup(Ogre::SceneManager* sceneManager);
	static Ogre::SceneManager* getSceneManager();

private:
	static Ogre::SceneManager* mSceneManager;
};


#endif