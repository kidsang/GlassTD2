#include "Monster.h"
#include "Cell.h"

#define CAN_STEP 0
#define NOT_STEP 1
#define HAS_STEP 2
#define SET_STEP 3

Monster::Monster(SceneNode* node)
	:mSpeed(1),
	mSpeedTemp(1),
	/*mPos(Ogre::Vector3(BEGIN_POS_X, 10, BEGIN_POS_Y)),*/
	mBlood(0),
    mFace(Ogre::Vector3(0, 0, 1)),
	mRadius(1),
	mType(),
	mHarmList(),
	mIsDead(false)
{
	mNode = node;
	mHarmCheck = new HarmCheck();
}
////
////Monster::Monster( SceneNode* node, Maze* maze )
////	:mSpeed(1),
////	mSpeedTemp(1),
////	/*mPos(Ogre::Vector3(BEGIN_POS_X, 10, BEGIN_POS_Y)),*/
////	mBlood(0),
////	mFace(Ogre::Vector3(0, 0, 1)),
////	mRadius(1),
////	mType(),
////	mHarmList(),
////	mIsDead(false)
////{
////	mNode = node;
////	mHarmCheck = new HarmCheck();
////	mMaze = maze;
////}

//
//Monster::Monster( Ogre::SceneManager* sceneMgr, Ogre::SceneNode* parentNode, Position& pos)
//{	
//	
//}

Monster::~Monster(void)
{
	/*if(mNode != NULL)
		delete mNode;*/
	delete mHarmCheck;
	delete mMaze;
}

//Ogre::SceneNode* Monster::getNode(Ogre::String mesh, Ogre::String name)
//{
//	
//	
//}

void Monster::go(float timeSinceLastFrame, Ogre::Vector3& direction)
{
	harmCheck(timeSinceLastFrame);
	mNode->setPosition(mNode->getPosition() + direction * timeSinceLastFrame * mSpeed);
	int* mp = new int[256];
	Ogre::Vector2* target = new Ogre::Vector2(Real(10), Real(10));
	Ogre::Vector2* start = new Ogre::Vector2(Real(2), Real(1));
	
}

float Monster::getBlood(void)
{
	return mBlood;
}
void Monster::setBlood(int mBlood)
{
	this->mBlood = mBlood;
}
std::string Monster::getType(void)
{
	return mType;
}


//Ogre::Vector3 Monster::getPosition(void)
//{
//	return mPos;
//}
//void Monster::setPosition(Ogre::Vector3& mPos)
//{
//	this->mPos = mPos;
//}
Ogre::Vector3 Monster::getFace()
{
	return mFace;
}
void Monster::setFace(Ogre::Vector3& mFace)
{
	this->mFace = mFace;
}

Ogre::String Monster::getMesh()
{
	return mMesh;
}

void Monster::setMesh( Ogre::String mesh )
{
	mMesh = mesh;
}

void Monster::setAnimate()
{
	Ogre::Entity* entity;
	entity = (Ogre::Entity*)mNode->getAttachedObject(0);
	mAnimationState = entity->getAnimationState("Walk");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
}

void Monster::addTimeToAnimation( float timeSinceLastFrame )
{
	mAnimationState->addTime(timeSinceLastFrame);
}

float Monster::getRadius()
{
	return mRadius;
}

void Monster::monsterScale( float x, float y, float z )
{
	mNode->scale(x, y, z);
}

void Monster::harmCheck(float timeSinceLastFrame)
{
	/// 先检查地形，更新怪物信息
	checkCellType();
	
	/// mHarmCheck->bulletHarm(mHarmList.h)
	mHarmCheck->fireHarmCheck(mHarmList.fireHarm, mHarmList.fireHarmTime, mBlood, timeSinceLastFrame);
	mHarmCheck->iceHarmCheck(mHarmList.iceHarm, mHarmList.iceHarmTime, mSpeed, mSpeedTemp, timeSinceLastFrame);
	mHarmCheck->spikeweedHarmCheck(mHarmList.spikeweedHarm, mBlood, mHarmList.isOnSpikeweed);
	mHarmCheck->swampHarmCheck(mHarmList.swampHarm, mSpeed, mSpeedTemp, mHarmList.isInSwamp);
	/// 判断是否死亡
	mIsDead = mHarmCheck->checkIsDead(mBlood);

}

bool Monster::isMonsterDead()
{
	return mIsDead;
}

void Monster::setHitByFire(float harm, float time)
{
	mHarmList.fireHarm = harm;
	mHarmList.fireHarmTime = time;
}



void Monster::setHitByIce(float harm, float time)
{
	mHarmList.iceHarm = harm;
	mHarmList.iceHarmTime = time;
}



void Monster::setBeCaughtByTrap()
{
	mHarmList.beCaught = true;
}

void Monster::setInsideSpikeweed()
{
    mHarmList.isOnSpikeweed = true;
}

void Monster::setOutsideSpikeweed()
{
	mHarmList.isOnSpikeweed = false;
}

void Monster::setInsideSwamp()
{
	mHarmList.isInSwamp = false;
}

void Monster::setOutsideSwamp()
{
	mHarmList.isInSwamp = false;
}

void Monster::setSpeed( float speed )
{
	mSpeed = speed;
	mSpeedTemp = speed;
}

void Monster::setRadius( float radius )
{
	mRadius = radius;
}

void Monster::setType( std::string type )
{
	mType = type;
}

void Monster::checkCellType()
{
	switch(mMaze->getCellByPos(mNode->getPosition())->getCellType())
	{
	case SPIKEWEED: setInsideSpikeweed(); setOutsideSwamp(); break;
	case TRAP:  setBeCaughtByTrap(); break;
	case SWAMP: setInsideSwamp(); setOutsideSpikeweed(); break;
	default: setOutsideSpikeweed(); setOutsideSwamp(); break;
	}
}

void Monster::checkHitBySpecialBullet(std::string bulletSpell, float bulletTime, float bulletHarm, float bulletAppendHarm)
{
	if(bulletSpell == "ice")
	{
		if(mType == "fire")
		{	
			mBlood -= bulletHarm;
			setHitByIce(bulletAppendHarm, bulletTime);
		}
		if(mType == "normal")
		{
			setHitByIce(bulletAppendHarm, bulletTime);
		}
	}
	
	if(bulletSpell == "fire")
	{
		
		if(mType != "fire")
		{
			setHitByFire(bulletAppendHarm, bulletTime);
		}
	}
}


bool Monster::isHitByBullet( float* bulletPos, float bulletRadius )
{
	float tempX, tempY;
	tempX = bulletPos[0] - mNode->getPosition()[0];
	tempY = bulletPos[2] - mNode->getPosition()[2];
	if(sqrt((tempX * tempX + tempY * tempY)) < bulletRadius + mRadius)
		return true;
	else 
		return false;
}

void Monster::checkHitByBullet( float* bulletPos, float bulletHarm, float bulletAppendHarm, float bulletTime, float bulletRadius, std::string bulletSpell )
{
	if(isHitByBullet(bulletPos, bulletRadius))
		mBlood -= bulletHarm;
	checkHitBySpecialBullet(bulletSpell, bulletTime, bulletHarm, bulletAppendHarm);
}

//Ogre::String Monster::getName()
//{
//	return mName;
//}
//
//void Monster::setName( Ogre::String name )
//{
//	mName = name;
//}


Monster* MonsterFactory::createInstance(SceneManager* sceneMgr)
{
	Ogre::SceneNode* monsterNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entity = sceneMgr->createEntity(mParams["mesh"]);
	monsterNode->attachObject(entity);
	Monster* mon;
	mon = new Monster(monsterNode);
	if (mParams.find("radius") != mParams.end())
		mon->setRadius((float)atof(mParams["radius"].c_str()));

	if (mParams.find("blood") != mParams.end())
		mon->setBlood((float)atof(mParams["blood"].c_str()));

	if (mParams.find("speed") != mParams.end())
		mon->setSpeed((float)atof(mParams["speed"].c_str()));

	if (mParams.find("spell") != mParams.end())
		mon->setType((mParams["spell"].c_str()));
	return mon;
}

std::string MonsterFactory::getType()
{
	return mType;
}
