#ifndef TracerBulletFactory_h__
#define TracerBulletFactory_h__

/**
 * �ļ���TracerBulletFactory
 * ���ڣ�2012/06/28
 * ���ߣ�kid
 */

#include "Bullet.h"

/// ҷ�ⵯ������
/// �������ڰ��������׼��ҷ�ⵯ
class TracerBulletFactory : public BulletFactory
{
public:
	TracerBulletFactory(NameValueList params);
	~TracerBulletFactory(void);

	Bullet* createInstance(SceneManager* mgr, BulletFactory* target);

private:
	/// �÷���������
	virtual Bullet* createInstance( SceneManager* mgr );

};

#endif // TracerBulletFactory_h__

