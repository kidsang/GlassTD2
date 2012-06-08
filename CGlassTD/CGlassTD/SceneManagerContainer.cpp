#include "SceneManagerContainer.h"

Ogre::SceneManager* SceneManagerContainer::mSceneManager = NULL;

void SceneManagerContainer::setup(Ogre::SceneManager* sceneManager)
{
	mSceneManager = sceneManager;
}

Ogre::SceneManager* SceneManagerContainer::getSceneManager()
{
	return mSceneManager;
}