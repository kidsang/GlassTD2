#include "Cannon.h"
#include "TracerBulletFactory.h"

Cannon::Cannon(SceneNode* gunNode, Entity* gun, SceneNode* swampNode, Entity* tire)
	: mGunNode(gunNode), mGun(gun), mTireNode(swampNode), mTire(tire), 
	mCurrentBullet(0),mFireOffset(Vector3(0.f)), mFireStrength(0), mColdDown(0), mFireAngle(Vector2(0.f)),
	mCurrentFireAngle(Vector2(0.f)), 
	mTarcerBulletFactory(0), mHasTracer(true), mTracerInterval(0.1f)
{
	/// ��ת���ڳ���
	mTireNode->setOrientation(0, 0, 1, 0);
	/// ��ʼ����ʱ��
	mTracerLastTime = mLastTime = clock();
	// ��ʼ���ڿ�
	mFirePositionNode = mGunNode->createChildSceneNode();
}

Cannon::~Cannon()
{
	// ����ڵ������б�
	for (auto iter = mBulletFactoryList.begin(); iter != mBulletFactoryList.end(); ++iter)
		delete (*iter);
	if (mTarcerBulletFactory)
		delete mTarcerBulletFactory;
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
	// ���㷢�䷽��
	Vector3 xAxis, yAxis, zAxis;
	mGunNode->_getDerivedOrientation().ToAxes(xAxis, yAxis, zAxis);
	// ��ȡ��ǰ���͵��ڵ�����
	BulletFactory* bf = mBulletFactoryList.at(mCurrentBullet);
	// �жϵ�ǰ��ҩ�Ƿ�������
	if (bf->getAmmoCount() <= 0)
		return NULL;
	// ���ݵ�ǰ��ѡ���ʹ����ڵ�
	Bullet* bul = bf->createInstance(mgr);
	bul->fire(mFirePositionNode->_getDerivedPosition(), zAxis * mFireStrength);

	mLastTime = clock();
	bf->setAmmoCount(bf->getAmmoCount() - 1);

	return bul;
}

Bullet* Cannon::fireTracer( SceneManager* mgr )
{
	// û��ҷ�ⵯ
	if (!mHasTracer || !mTarcerBulletFactory)
		return NULL;

	if (clock() < mTracerLastTime + mTracerInterval * 1000)
		return NULL;
	
	// ���㷢�䷽��
	Vector3 xAxis, yAxis, zAxis;
	mGunNode->_getDerivedOrientation().ToAxes(xAxis, yAxis, zAxis);

	// ��ȡ��ǰ���͵��ڵ�����
	BulletFactory* bf = mBulletFactoryList.at(mCurrentBullet);

	// ���ݵ�ǰ�ڵ�����ҷ�ⵯ 
	Bullet* bul = mTarcerBulletFactory->createInstance(mgr, bf);
	bul->fire(mFirePositionNode->_getDerivedPosition(), zAxis * mFireStrength);

	mTracerLastTime = clock();

	return bul;
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
	float factor = 400.f; // ������̨����ת�ٶ�
	float fyaw = (float)yaw / factor;
	float fpitch = (float)pitch / factor;

	mCurrentFireAngle += Vector2(fyaw, fpitch);

	// ������̨ת��
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
	// ��ת�ڹ�
	//mTireNode->yaw(Ogre::Radian(fyaw), Ogre::Node::TS_WORLD);
	//mGunNode->pitch(Ogre::Radian(fpitch), Ogre::Node::TS_WORLD);
	mTireNode->yaw(Ogre::Radian(fyaw));
	mGunNode->pitch(Ogre::Radian(fpitch));
	cam->yaw(Ogre::Radian(fyaw));
}

