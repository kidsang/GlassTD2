#include "Bullet.h"
#include <OgreEntity.h>
#include <Ogre.h>

Bullet::Bullet(SceneManager* manager, SceneNode* node, Entity* entity)
	: mSceneManager(manager), mNode(node), mEntity(entity),
	mIsFired(false),
	mMass(1), mDamage(0), mRange(0), mSpell("normal"), mEffectTime(0)
{
}


Bullet::~Bullet(void)
{
	// É¾³ýÅÚµ¯mesh
	auto objIter = mNode->getAttachedObjectIterator();
	while (objIter.hasMoreElements())
		mSceneManager->destroyMovableObject(objIter.getNext());
	// É¾³ýÅÚµ¯µÄ³¡¾°½Úµã
	mSceneManager->destroySceneNode(mNode);
}

void Bullet::fire(const Vector3& position, const Vector3& velocity)
{
	mIsFired = true;
	mPosition = position;
	mVelocity = velocity;
}

void Bullet::fly(float t, const Vector3& gravity)
{
	if (!mIsFired)
		return;

	// ¸üÐÂÅÚµ¯Î»ÖÃ
	mVelocity += gravity * getMass() * t;
	mPosition += mVelocity * t;
	mNode->setPosition(mPosition);
}

Bullet* BulletFactory::createInstance( SceneManager* mgr )
{
	SceneNode* node = mgr->getRootSceneNode()->createChildSceneNode();
	Entity* entity = mgr->createEntity(mParams["mesh"]);
	if (mParams.find("material") != mParams.end())
		entity->setMaterialName(mParams["material"]);
	node->attachObject(entity);

	Bullet* bullet = new Bullet(mgr, node, entity);
	
	bullet->setType(mType);

	if (mParams.find("scale") != mParams.end())
		node->setScale(Vector3((float)atof(mParams["scale"].c_str())));

	if (mParams.find("mass") != mParams.end())
		bullet->setMass((float)atof(mParams["mass"].c_str()));

	if (mParams.find("damage") != mParams.end())
		bullet->setDamage((float)atof(mParams["damage"].c_str()));

	if (mParams.find("appendDamage") != mParams.end())
		bullet->setAppendDamage((float)atof(mParams["appendDamage"].c_str()));

	if (mParams.find("range") != mParams.end())
		bullet->setRange((float)atof(mParams["range"].c_str()));

	if (mParams.find("spell") != mParams.end())
		bullet->setSpell(mParams["spell"]);

	if (mParams.find("time") != mParams.end())
		bullet->setEffectTime((float)atof(mParams["time"].c_str()));

	if (mParams.find("flare") != mParams.end())
	{
		ParticleSystem* ps = mgr->createParticleSystem(node->getName() + "Flare", mParams["flare"]);
		node->attachObject(ps);
	}

	return bullet;
}

BulletFactory::BulletFactory( NameValueList params ) :mParams(params), mType("NormalBullet"), mAmmo(0)
{
	if (params.find("name") != params.end())
		mType = params["name"];
	if (params.find("ammo") != params.end())
		mAmmo = atoi(params["ammo"].c_str());
}
