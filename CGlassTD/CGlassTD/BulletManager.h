#ifndef __BulletManager_h_
#define __BulletManager_h_

#include "Bullet.h"
#include "List.hpp"
#include <map>
using namespace Ogre;

class BillboardSprite;

/// 炮弹管理类
class BulletManager
{
private:
	MyList<Bullet*> mBulletList;
	MyList<BillboardSprite*> mExplodeSprites;

public:
	BulletManager(void);
	~BulletManager(void);

	/// 添加一个炮弹
	/// @param bullet 要被添加的炮弹
	void add(Bullet* bullet);

	/// 使炮弹飞行
	/// @param timeSinceLastFrame 上一帧持续时间
	/// @param gravity 环境重力
	void fly(float timeSinceLastFrame, const Ogre::Vector3& gravity);

	/// 返回爆炸的炮弹，并将它们从列表中删除
	/// @param floor 地板高度
	/// @param sceneMgr 场景管理类
	std::vector<NameValueList> getAndRemoveExplodedBullets(float floor, SceneManager* sceneMgr);

	/// 播放炮弹的爆炸动画
	/// @param timeSinceLastFrame 上一帧持续时间
	void runExplodeAnimator(float timeSinceLastFrame);
};


#endif

