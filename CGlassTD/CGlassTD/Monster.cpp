#include "Monster.h"
#include "Cell.h"

#define CAN_STEP 0
#define NOT_STEP 1
#define HAS_STEP 2
#define SET_MARK 3

Monster::Monster(SceneNode* node)
	:mSpeed(1),
	mSpeedTemp(1),
	/*mPos(Ogre::Vector3(BEGIN_POS_X, 10, BEGIN_POS_Y)),*/
	mBlood(0),
    mFace(Ogre::Vector3(0, 0, 1)),
	mRadius(1),
	mType(),
	mHarmList(),
	mIsDead(false),
	mBeginPosIndex(0),
    mNextPosIndex(1)
{
	mNode = node;
	mHarmCheck = new HarmCheck();
	
}

Monster::Monster(SceneNode* node, Maze* maze)
	:mSpeed(1),
	mSpeedTemp(1),
	/*mPos(Ogre::Vector3(BEGIN_POS_X, 10, BEGIN_POS_Y)),*/
	mBlood(0),
	mFace(Ogre::Vector3(0, 0, 1)),
	mRadius(1),
	mType(),
	mHarmList(),
	mIsDead(false),
	mBeginPosIndex(0),
	mNextPosIndex(1)
{
	mNode = node;
	mMaze = maze;
	mHarmCheck = new HarmCheck();
	ogrePath.push_back(Ogre::Vector3(0, 0, 0));
	ogrePath.push_back(Ogre::Vector3(10, 0, 0));
	ogrePath.push_back(Ogre::Vector3(10, 0, 10));
	ogrePath.push_back(Ogre::Vector3(15, 0, 15));
	ogrePath.push_back(Ogre::Vector3(20, 0, 30));
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

void Monster::go(float timeSinceLastFrame)
{
	
	/*if(ogrePath[mNextPosIndex] - mNode->getPosition() < Ogre::Vector3(1, 1, 1))
	{
	mNode->setPosition(ogrePath[mNextPosIndex]);
	if(ogrePath[ogrePath.size()-1] != mNode->getPosition())
	{
	mBeginPosIndex++;
	mNextPosIndex++;
	}
	}
	harmCheck(timeSinceLastFrame);
	mNode->setPosition(mNode->getPosition() + (ogrePath[mNextPosIndex] - ogrePath[mBeginPosIndex]) * timeSinceLastFrame * mSpeed);
	*/
	mNode->setPosition(mNode->getPosition() + Ogre::Vector3(20, 0, 0) * timeSinceLastFrame * mSpeed);

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
	mHarmCheck->spikeweedHarmCheck(mHarmList.spikeweedHarm, mBlood, mHarmList.isOnSpikeweed, timeSinceLastFrame);
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

void Monster::makeMap( Cell* cells )
{
	this->mMapHeight = mMaze->getMapHeight();
	this->mMapWidth = mMaze->getMapWidth();
	Ogre::Vector3 t = mMaze->getFinalPos();
	finalPos.x = (int)t.x;
	finalPos.y = (int)t.z;
	startPos = std::vector<Pos>();
	ogrePath = std::vector<Ogre::Vector3>();
	path = std::vector<Pos>();
	std::vector<Ogre::Vector3> temp = mMaze->getStartPos();
	for(auto iter = temp.begin();iter != temp.end(); ++iter)
	{
		Ogre::Vector3 v3 = (*iter);
		Pos p;
		p.x = (int)v3.x;
		p.y = (int)v3.z;
		startPos.push_back(p);
	}
	map = new int *[mMapHeight];
	for(int j = 0; j < mMapHeight; ++j)
	{
		map[j] = new int[mMapWidth];
	}
	for(int i = 0; i < mMapWidth * mMapHeight; ++i)
	{
		if(cells[i].getCellType() == FREE)
		{
			map[i / mMapHeight][i % mMapHeight] = CAN_STEP;
		}
		else
		{
			map[i / mMapHeight][i % mMapHeight] = NOT_STEP;
		}
	}
}

bool Monster::isValid( Pos pos )
{
	if((pos.x>=0) && (pos.x<mMapWidth) && (pos.y>=0) && (pos.y<mMapHeight))
		return true;
	else
		return false;
}

bool Monster::isFinal( Pos pos )
{
	if((finalPos.x == pos.x) && (finalPos.y == pos.y))
		return true;
	else
		return false;
}

void Monster::markIt( Pos pos )
{
	map[pos.x][pos.y] = SET_MARK;
}

void Monster::stepTo( Pos pos )
{
	map[pos.x][pos.y] = HAS_STEP;
}

void Monster::pushPos( Pos pos, stack<CellNode>& st )
{
	Vect vect[4];                       //上下左右4个方向向量
	vect[0].dx = 0;  vect[0].dy = 1;    //vect[0] = {0, 1};
	vect[1].dx = 1;  vect[1].dy = 0;    //vect[1] = {1, 0};
	vect[2].dx = -1; vect[2].dy = 0;    //vect[2] = {-1, 0};
	vect[3].dx = 0;  vect[3].dy = -1;   //vect[3] = {0, -1};

	//判断在这4个方向向量中哪几个可以步进
	Judge* head = NULL;
	Judge* ptr = NULL;
	Judge* tmp = NULL;
	bool lock = false;
	Pos now;
	int dist;
	for(int i=0; i<4; i++)
	{
		now.x = pos.x + vect[i].dx;
		now.y = pos.y + vect[i].dy;
		//检测当前位置是否越界且可步进
		if(isValid(now))
			if(map[now.x][now.y]==CAN_STEP)
			{
				//对当前节点进行评估
				dist = abs(now.x-finalPos.x) + abs(now.y-finalPos.y);

				Judge* judge = new Judge();
				judge->node.pare = pos;
				judge->node.self = now;
				judge->node.dist = dist;
				judge->next = NULL;
				if(!lock)
				{
					//第一个节点作表头
					head = judge;
					lock = true;
				}
				else
				{
					//如果当前位置到终点的距离最大则作为新表头
					if(judge->node.dist >= head->node.dist)
					{
						judge->next = head;
						head = judge;
					}
					else
					{
						//如果当前位置到终点的距离不是最大则插入到表中的合适位置
						bool in = false;
						ptr = head;
						while(ptr != NULL)
						{
							if(judge->node.dist >= ptr->node.dist)
							{
								judge->next = ptr;
								tmp->next = judge;
								in = true;
							}
							tmp = ptr;
							ptr = ptr->next;
						}
						//如果当前位置到终点的距离最小则插入到表尾
						if(!in)
						{
							tmp->next = judge;
						}
					}
				}
			}
	}

	/// 将表中存储的位置信息压入堆栈
	ptr = head;
	while(ptr != NULL)
	{
		st.push(ptr->node);
		tmp = ptr;
		ptr = ptr->next;
	}
}

bool Monster::findPath( Pos sour )
{
	Pos** record;
	record = new Pos *[mMapHeight];
	for(int i = 0; i < mMapHeight; ++i)
	{
		record[i] = new Pos[mMapWidth];
	}
	stack<CellNode> st = stack<CellNode>();
	CellNode node;
	node.self = sour;
	st.push(node);

	//判断从起点到终点之间是否有通路
	CellNode temp;
	while(true)
	{
		if(!st.empty())
		{
			temp = st.top();
			st.pop();
		}
		else
		{
			return false;
		}
		if(isFinal(temp.self))
		{
			if(isValid(temp.self))
			{
				markIt(temp.self);
				record[temp.self.x][temp.self.y] = temp.pare;
			}
			break;
		}
		else
		{
			if(isValid(temp.self))
			{
				markIt(temp.self);
				record[temp.self.x][temp.self.y] = temp.pare;
				pushPos(temp.self, st);
			}
		}
	}

	//// 如果有通路则寻找合适的路径
	Pos parent = finalPos;
	bool success = false;
	while(isValid(parent) && !success)
	{
		stepTo(parent);
		path.push_back(getStep());
		markIt(parent);
		parent = record[parent.x][parent.y];
		if(parent.x==sour.x && parent.y==sour.y)
		{
			success = true;
		}
	}
	path.push_back(finalPos);
	return true;
}

Pos Monster::getStep()
{
	for(int i=0; i<mMapHeight; i++)
	{
		for(int j=0; j<mMapWidth; j++)
		{

			if(map[i][j] == 2)
			{
				Pos p;
				p.x = j;
				p.y = i;
				return p;
			}
		}
	}

}

void Monster::transPos()
{
	for(auto it = path.begin(); it != path.end(); ++it)
	{
		ogrePath.push_back((*mMaze->translatePos(new Ogre::Vector3(Real((*it).x), Real(0), Real((*it).y)))));
	}
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
	mon->setAnimate();
	return mon;
}

Monster* MonsterFactory::createInstance(SceneManager* sceneMgr, Maze* maze)
{
	Ogre::SceneNode* monsterNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entity = sceneMgr->createEntity(mParams["mesh"]);
	monsterNode->attachObject(entity);
	Monster* mon;
	mon = new Monster(monsterNode, maze);
	if (mParams.find("radius") != mParams.end())
		mon->setRadius((float)atof(mParams["radius"].c_str()));

	if (mParams.find("blood") != mParams.end())
		mon->setBlood((float)atof(mParams["blood"].c_str()));

	if (mParams.find("speed") != mParams.end())
		mon->setSpeed((float)atof(mParams["speed"].c_str()));

	if (mParams.find("spell") != mParams.end())
		mon->setType((mParams["spell"].c_str()));
	mon->setAnimate();
	return mon;
}

std::string MonsterFactory::getType()
{
	return mType;
}
