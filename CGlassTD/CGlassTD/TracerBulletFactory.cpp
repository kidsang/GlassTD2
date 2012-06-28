#include "TracerBulletFactory.h"
#include "Ogre.h"

TracerBulletFactory::TracerBulletFactory(NameValueList params)
	: BulletFactory(params)
{
}


TracerBulletFactory::~TracerBulletFactory(void)
{
}

Bullet* TracerBulletFactory::createInstance( SceneManager* mgr )
{
	throw std::exception("The method or operation is not implemented.");
}

Bullet* TracerBulletFactory::createInstance( SceneManager* mgr, BulletFactory* target )
{
	SceneNode* node = mgr->getRootSceneNode()->createChildSceneNode();

	Bullet* bullet = new Bullet(mgr, node, NULL);
	NameValueList targetParams = target->getParams();

	bullet->setType(mType);

	if (mParams.find("flare") != mParams.end())
	{
		ParticleSystem* ps = mgr->createParticleSystem(node->getName() + "Flare", mParams["flare"]);
		node->attachObject(ps);
	}

	if (targetParams.find("mass") != targetParams.end())
		bullet->setMass((float)atof(targetParams["mass"].c_str()));

	return bullet;
}
