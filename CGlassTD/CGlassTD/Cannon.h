#ifndef __Cannon_h_
#define __Cannon_h_

#include <vector>
#include "Bullet.h"
#include "OgreQuaternion.h"
#include <time.h>
class TracerBulletFactory;

/// ��̨��
/// @author: LiaoNanhao
class Cannon
{
	typedef std::vector<BulletFactory*> BulletFactoryList;

private:
	/// ��̨��ӵ�е������ڵ�
	BulletFactoryList mBulletFactoryList;
	/// ��ǰѡ��ĵ�ҩ����
	unsigned int mCurrentBullet;

	/// ҷ�ⵯ
	TracerBulletFactory* mTarcerBulletFactory;
	/// �Ƿ���ҷ�ⵯ
	bool mHasTracer;
	/// ҷ�ⵯ������
	float mTracerInterval;
	/// ҷ�ⵯ�ϴη���ʱ��
	clock_t mTracerLastTime;

	/// ���ڷ�������
	float mFireStrength;
	/// �ڿڵ�λ��ƫ����
	Vector3 mFireOffset;
	/// ���ڵķ�����,�������
	float mColdDown;
	/// ���ڵ��������
	Vector2 mFireAngle;

	/// �ϴη����ʱ��
	clock_t mLastTime;
	/// ���ڵ�ǰ���
	Vector2 mCurrentFireAngle;

	/// �ڹܵĽڵ�
	SceneNode* mGunNode;
	/// �ڹܵ�ģ��
	Entity* mGun;
	/// ��̨�Ľڵ�
	SceneNode* mTireNode;
	/// ��̨��ģ��
	Entity* mTire;
	/// �ڿڽڵ�
	SceneNode* mFirePositionNode;

public:
	Cannon(SceneNode* gunNode, Entity* gun, SceneNode* swampNode, Entity* tire);
	~Cannon();

	/// ����̨����һ���ڵ�����
	/// @param bulletFactory Ҫ���ӵ��ڵ�����
	/// @note һ���ڵ�����ʵ���Ͼ���ĳ���ڵ���
	///		  ����Ϊ��������̨���Ӳ�ͬ������ڵ�
	void addBulletFactory(BulletFactory* bulletFactory);

	/// ���䵱ǰװ�����ڵ�
	/// @return ���ط�����ڵ����������ʧ��(����cd)�򷵻�NULL
	/// @note �ⲿ��ĳ��������Ӧ�ý��ַ����ȥ���ڵ��Ĺ�������
	///		  ���������fly()�������ͷ���Դ��
	Bullet* fire(SceneManager* mgr);
	
	/// ����ҷ�ⵯ
	/// @return ���ط�����ڵ����������ʧ��(����cd)�򷵻�NULL
	Bullet* fireTracer(SceneManager* mgr);

	/// ���ĵ�ǰװ�����ڵ�
	/// @param index �ڼ����ڵ�
	/// @note ������Ƿ�����ʱ���Ȳ��������Ҳ����ʾ�κδ���
	void changeBullet(unsigned int index);

	/// �л�����һ������
	/// @note ����ת
	void changeBullet();

	/// �޸���̨����
	void rotate(int yaw, int pitch, Ogre::Camera* cam);

	// Get/Set
public:
	/// ����ҷ�ⵯ
	void setTracer(TracerBulletFactory* tbf)
	{
		mTarcerBulletFactory = tbf;
	}

	/// �����Ƿ�����ҷ�ⵯ
	bool hasTracer()
	{
		return mHasTracer;
	}

	/// �����Ƿ�����ҷ�ⵯ
	void setTracerEnable(bool isEnable)
	{
		mHasTracer = isEnable;
	}

	/// �����ڵ������б�
	const BulletFactoryList& getBulletFactories()
	{
		return mBulletFactoryList;
	}

	/// ���ش��ڵĽڵ�
	const SceneNode* getCannonNode()
	{
		return mGunNode;
	}

	/// ���ش��ڵ��������
	const Vector2& getFireAngle()
	{
		return mFireAngle;
	}

	/// ���ô��ڵ��������
	void setFireAngle(const Vector2& angle)
	{
		mFireAngle = angle;
	}

	/// ���ش��ڷ�������
	const float getFireStrenth()
	{
		return mFireStrength;
	}

	/// ���ô��ڷ�������
	void setFireStrength(float strength)
	{
		mFireStrength = strength;
	}

	/// �����ڵ�����λ�õ�ƫ����(���ڿ�λ��)
	const Vector3& getFireOffset()
	{
		//return mFireOffset;
		return mFirePositionNode->getPosition();
	}

	/// �����ڵ�����λ�õ�ƫ����(���ڿ�λ��)
	void setFireOffset(const Vector3& offset)
	{
		//mFireOffset = offset;
		mFirePositionNode->setPosition(offset);
	}

	/// ���ش��ڷ�����
	const float getColdDown()
	{
		return mColdDown;
	}

	/// ���ô��ڷ�����
	void setColdDown(float coldDown)
	{
		mColdDown = coldDown;
	}
	///���ص�ǰ�ڵ�����
	unsigned int getCurrentBullet()
	{
		return mCurrentBullet;
	}
};


#endif
