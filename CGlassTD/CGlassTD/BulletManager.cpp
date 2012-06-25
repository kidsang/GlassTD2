#include "BulletManager.h"
#include "BillboardSpriteAnimator.h"


BulletManager::BulletManager(void)
{
}


BulletManager::~BulletManager(void)
{
	mBulletList.start();
	while (mBulletList.forward())
		delete mBulletList.getData();
	mBulletList.clear();

	mExplodeSprites.start();
	while (mExplodeSprites.forward())
		delete mExplodeSprites.getData();
	mExplodeSprites.clear();
}

void BulletManager::add( Bullet* bullet )
{
	mBulletList.insertAhead(bullet);
}

void BulletManager::fly( float timeSinceLastFrame, const Ogre::Vector3& gravity )
{
	mBulletList.start();
	while (mBulletList.forward())
		mBulletList.getData()->fly(timeSinceLastFrame, gravity);
}

std::vector<NameValueList> BulletManager::getAndRemoveExplodedBullets(float floor, SceneManager* sceneMgr)
{
	std::vector<NameValueList> exploded;

	mBulletList.start();
	while (mBulletList.forward())
		if (mBulletList.getData()->getPosition().y < floor)
		{
			Bullet* bul = mBulletList.getData();
			// 增加爆炸动画
			BillboardSet* explode = sceneMgr->createBillboardSet(2U);
			explode->setDefaultDimensions(800, 800);
			explode->setMaterialName("Glass/SpriteExplode");
			explode->createBillboard(0, 0, 0);
			SceneNode* expNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
			expNode->setPosition(bul->getPosition());
			expNode->attachObject(explode);
			BillboardSprite* bs = new BillboardSprite(expNode, explode, 5, 4, 192, 192);
			BillboardSpriteAnimator* bsani = new BillboardSpriteAnimator(0);
			bsani->start(bs);
			bs->addAnimator(bsani);
			mExplodeSprites.insertAhead(bs);

			// 将爆炸节点的信息储存
			NameValueList nvl;
			nvl.insert(std::make_pair("appendDamage", convertToString(bul->getAppendDamage())));
			nvl.insert(std::make_pair("damage", convertToString(bul->getDamage())));
			nvl.insert(std::make_pair("range", convertToString(bul->getRange())));
			nvl.insert(std::make_pair("time", convertToString(bul->getEffectTime())));
			nvl.insert(std::make_pair("spell", bul->getSpell()));
			nvl.insert(std::make_pair("position",
				convertToString(bul->getPosition().x)
				+ " " + convertToString(bul->getPosition().y)
				+ " " + convertToString(bul->getPosition().z)));
			exploded.push_back(nvl);
			// 删除爆炸的节点
			delete bul;
			mBulletList.deleteCurrentNode();
		}

	return exploded;
}

void BulletManager::runExplodeAnimator( float timeSinceLastFrame )
{
	mExplodeSprites.start();
	while (mExplodeSprites.forward())
	{
		BillboardSprite* bs = mExplodeSprites.getData();
		bs->animate(timeSinceLastFrame, bs);
		if (bs->getFinish())
		{
			delete bs;
			mExplodeSprites.deleteCurrentNode();
		}
	}
}
