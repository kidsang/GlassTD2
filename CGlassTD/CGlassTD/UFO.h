
#ifndef __UFO_h_
#define __UFO_h_

#include <Ogre.h>
using namespace Ogre;

/// UFO类
/// 定义了凹凸曼星人的总部
class UFO
{
private:
	int mBlood;
	int mMaxBlood;
	Ogre::SceneNode* mNode;
	Ogre::Entity* mEntity;
	/// UFO头顶血条
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

