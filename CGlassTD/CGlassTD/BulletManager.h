#ifndef __BulletManager_h_
#define __BulletManager_h_

#include "Bullet.h"
#include "List.hpp"
#include <map>
using namespace Ogre;

class BillboardSprite;

/// �ڵ�������
class BulletManager
{
private:
	MyList<Bullet*> mBulletList;
	MyList<BillboardSprite*> mExplodeSprites;

public:
	BulletManager(void);
	~BulletManager(void);

	/// ���һ���ڵ�
	/// @param bullet Ҫ����ӵ��ڵ�
	void add(Bullet* bullet);

	/// ʹ�ڵ�����
	/// @param timeSinceLastFrame ��һ֡����ʱ��
	/// @param gravity ��������
	void fly(float timeSinceLastFrame, const Ogre::Vector3& gravity);

	/// ���ر�ը���ڵ����������Ǵ��б���ɾ��
	/// @param floor �ذ�߶�
	/// @param sceneMgr ����������
	std::vector<NameValueList> getAndRemoveExplodedBullets(float floor, SceneManager* sceneMgr);

	/// �����ڵ��ı�ը����
	/// @param timeSinceLastFrame ��һ֡����ʱ��
	void runExplodeAnimator(float timeSinceLastFrame);
};


#endif

