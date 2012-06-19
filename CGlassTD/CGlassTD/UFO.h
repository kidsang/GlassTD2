
#ifndef __UFO_h_
#define __UFO_h_

#include <Ogre.h>
using namespace Ogre;

class UFO
{
private:
	int mBlood;
	int mMaxBlood;
	Ogre::SceneNode* mNode;
	Ogre::Entity* mEntity;
	/// UFOÍ·¶¥ÑªÌõ
	BillboardSet* mHealthHUD;

public:
	UFO(Ogre::SceneNode* node, Ogre::Entity* entity, int blood);
	~UFO(void);

	void setBlood(int blood);

	int getBlood()
	{
		return mBlood;
	}

	bool isDestroy()
	{
		return (mBlood <= 0);
	}

	void setHealthHUD(BillboardSet* health)
	{
		mHealthHUD = health;
	}
};

#endif

