#include "UFO.h"
#include "ObjectFactory.h"

UFO::UFO(Ogre::SceneNode* node, Ogre::Entity* entity, int blood)
	: mNode(node), mEntity(entity), mBlood(blood), mMaxBlood(blood), mHealthHUD(0)
{
}


UFO::~UFO(void)
{
	if (mHealthHUD)
	{
		mHealthHUD->clear();
		delete mHealthHUD;
		mHealthHUD = 0;
	}
}

void UFO::setBlood( int blood )
{
	mBlood = blood;
	/// 改变头顶血量显示
	Billboard* health = mHealthHUD->getBillboard(0);
	float healthPer = mBlood / (float)mMaxBlood;
	float healthLength = healthPer * mHealthHUD->getDefaultWidth();
	health->setDimensions(healthLength, mHealthHUD->getDefaultHeight());
	ColourValue maxHealthCol = ColourValue(0, 0.8f, 0);
	ColourValue minHealthCol = ColourValue(1, 0, 0);
	ColourValue currHealthCol = maxHealthCol * healthPer + minHealthCol * (1 - healthPer);
	health->setColour(currHealthCol);
}
