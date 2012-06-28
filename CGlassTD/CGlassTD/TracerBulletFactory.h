#ifndef TracerBulletFactory_h__
#define TracerBulletFactory_h__

/**
 * 文件：TracerBulletFactory
 * 日期：2012/06/28
 * 作者：kid
 */

#include "Bullet.h"

class TracerBulletFactory : public BulletFactory
{
public:
	TracerBulletFactory(NameValueList params);
	~TracerBulletFactory(void);

	Bullet* createInstance(SceneManager* mgr, BulletFactory* target);

private:
	/// 该方法被隐藏
	virtual Bullet* createInstance( SceneManager* mgr );

};

#endif // TracerBulletFactory_h__

