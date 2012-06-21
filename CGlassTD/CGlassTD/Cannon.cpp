#include "Cannon.h"

Cannon::Cannon(SceneNode* gunNode, Entity* gun, SceneNode* swampNode, Entity* tire)
	: mGunNode(gunNode), mGun(gun), mTireNode(swampNode), mTire(tire), 
	mCurrentBullet(0),mFireOffset(Vector3(0.f)), mFireStrength(0), mColdDown(0), mFireAngle(Vector2(0.f)),
	mCurrentFireAngle(Vector2(0.f))
{
	/// 翻转大炮朝向
	mTireNode->setOrientation(0, 0, 1, 0);
	/// 初始化计时器
	mLastTime = clock();
	// 初始化炮口
	mFirePositionNode = mGunNode->createChildSceneNode();
}

Cannon::~Cannon()
{
	// 清空炮弹工厂列表
	for (auto iter = mBulletFactoryList.begin(); iter != mBulletFactoryList.end(); ++iter)
		delete (*iter);
	//
	delete mGunNode->getAttachedObject(0);
	delete mTireNode->getAttachedObject(0);
	mTireNode->getParentSceneNode()->removeAndDestroyChild(mTireNode->getName());
}

void Cannon::addBulletFactory( BulletFactory* bulletFactory )
{
	mBulletFactoryList.push_back(bulletFactory);
}

Bullet* Cannon::fire(SceneManager* mgr)
{
	if (clock() < mLastTime + mColdDown * 1000)
		return NULL;
	// 计算发射方向
	Vector3 xAxis, yAxis, zAxis;
	mGunNode->_getDerivedOrientation().ToAxes(xAxis, yAxis, zAxis);
	// 获取当前类型的炮弹工厂
	BulletFactory* bf = mBulletFactoryList.at(mCurrentBullet);
	// 判断当前弹药是否还有余量
	if (bf->getAmmoCount() <= 0)
		return NULL;
	// 根据当前所选类型创建炮弹
	Bullet* bul = bf->createInstance(mgr);
	//bul->fire(mTireNode->getPosition() + mFireOffset,zAxis * mFireStrength);
	bul->fire(mFirePositionNode->_getDerivedPosition(), zAxis * mFireStrength);
	//bul->fire(Ogre::Vector3(-397,100,400),zAxis * mFireStrength);

	mLastTime = clock();
	bf->setAmmoCount(bf->getAmmoCount() - 1);

	return bul;
	return NULL;
}

void Cannon::changeBullet( unsigned int index )
{
	if (index >= mBulletFactoryList.size())
		return;
	mCurrentBullet = index;
}

void Cannon::changeBullet()
{
	mCurrentBullet = (mCurrentBullet + 1) % mBulletFactoryList.size();
}

void Cannon::rotate( int yaw, int pitch, Ogre::Camera* cam)
{
	float factor = 400.f; // 调整炮台的旋转速度
	float fyaw = (float)yaw / factor;
	float fpitch = (float)pitch / factor;

	mCurrentFireAngle += Vector2(fyaw, fpitch);

	// 限制炮台转角
	if (mCurrentFireAngle.x > mFireAngle.x)
	{
		fyaw -= mCurrentFireAngle.x - mFireAngle.x;
		mCurrentFireAngle.x = mFireAngle.x;
	}
	else if (mCurrentFireAngle.x < -mFireAngle.x)
	{
		fyaw -= mCurrentFireAngle.x + mFireAngle.x;
		mCurrentFireAngle.x = -mFireAngle.x;
	}
	if (mCurrentFireAngle.y > mFireAngle.y)
	{
		fpitch -= mCurrentFireAngle.y - mFireAngle.y;
		mCurrentFireAngle.y = mFireAngle.y;
	}
	else if (mCurrentFireAngle.y < -mFireAngle.y)
	{
		fpitch -= mCurrentFireAngle.y + mFireAngle.y;
		mCurrentFireAngle.y = -mFireAngle.y;
	}
	// 旋转炮管
	//mTireNode->yaw(Ogre::Radian(fyaw), Ogre::Node::TS_WORLD);
	//mGunNode->pitch(Ogre::Radian(fpitch), Ogre::Node::TS_WORLD);
	mTireNode->yaw(Ogre::Radian(fyaw));
	mGunNode->pitch(Ogre::Radian(fpitch));
	cam->yaw(Ogre::Radian(fyaw));
}
