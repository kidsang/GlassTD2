#ifndef __BulletManager_h_
#define __BulletManager_h_

#include "Bullet.h"
#include "List.hpp"
#include <map>
using namespace Ogre;

class BillboardSprite;

class BulletManager
{
private:
	MyList<Bullet*> mBulletList;
	MyList<BillboardSprite*> mExplodeSprites;

public:
	BulletManager(void);
	~BulletManager(void);

	void add(Bullet* bullet);
	void fly(float timeSinceLastFrame, const Ogre::Vector3& gravity);
	std::vector<NameValueList> getAndRemoveExplodedBullets(float floor, SceneManager* sceneMgr);
	void runExplodeAnimator(float timeSinceLastFrame);
};


#endif

