#include "Monster.h"
#include "Cell.h"
#include <algorithm>
#include "MonsterHurtAnimator.h"
#include "Sound.h"
#include "Stage.h"
#define CAN_STEP 0
#define NOT_STEP 1
#define HAS_STEP 2
#define SET_MARK 3

Monster::Monster(SceneNode* node, Maze* maze, MonsterManager* monsterMgr)
	:
	mMonsterManager(monsterMgr),
	mSpeed(1),
	mSpeedTemp(1),
	/*mPos(Ogre::Vector3(BEGIN_POS_X, 10, BEGIN_POS_Y)),*/
	mBlood(0),
	mMaxBlood(0),
	mFace(Ogre::Vector3(0, 0, 0)),
	mRadius(1),
	mType(),
	//mHarmList(),
	mIsDead(false),
	mBeginPosIndex(-1),
	mNextPosIndex(0),
	mDistance(-0.1f),
	mBulletHarmTime(0),
	mBulletHarmValue(0),
	mTerrainHarmvalue(0),
	mHealthHUD(0),
	mIsGetUFO(false)
{
	mNode = node;
	mMaze = maze;
	mCheckMethod = new CheckMethod();
	mMonsterState = new MonsterState();

	//mNode->setOrientation(0, 0, 1, 0);
	makeMap(mMaze->getMazeInfo());
	int i = rand() % startPos.size();
	fromPos = startPos[i];
	findPath(fromPos);
	this->transPos();
}

Monster::~Monster(void)
{
	if (mHealthHUD)
	{
		mHealthHUD->clear();
		delete mHealthHUD;
		mHealthHUD = 0;
	}
	/*for (auto iter = mAnimatorList.begin(); iter != mAnimatorList.end(); ++iter)
		delete (*iter);*/
	if(mNode)
	{
		MovableObject* obj = mNode->getAttachedObject(0);
		delete obj;
		mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());
		mNode = 0;
	}
	if (mCheckMethod)
	{
		delete mCheckMethod;
		mCheckMethod = 0;
	}
	if (mMonsterState)
	{
		delete mMonsterState;
		mMonsterState = 0;
	}
	
}



void Monster::go(float timeSinceLastFrame)
{
	
	/// 给动画增加时间
	addTimeToAnimation(timeSinceLastFrame);
	if(!mIsDead)
	{
		if(mDistance < 0.0f || mDistance == 0.0f)
		{
			int size = ogrePath.size();
			mNode->setPosition(ogrePath[mNextPosIndex]);
			if(ogrePath[ogrePath.size()-1] != mNode->getPosition())
			{
				mBeginPosIndex++;
				mNextPosIndex++;
				mDistance = distance(ogrePath[mNextPosIndex], ogrePath[mBeginPosIndex]);
				/// 面向，方向向量
				mFace = (ogrePath[mNextPosIndex] - ogrePath[mBeginPosIndex]);
				mFace.normalise();
			
				/// 旋转面向角度
				Ogre::Vector3 src = mNode->getOrientation() * Vector3::UNIT_X; 
				Ogre::Quaternion quat = src.getRotationTo(mFace);
				mNode->rotate(quat);
			}
			else
			{
				setBlood(0);
				mIsGetUFO = true;
			}
		}
	
		/// 平移所需要走的路
		float moveDistance =  timeSinceLastFrame * mSpeed;
		mNode->translate(mFace * moveDistance);
		mDistance -= moveDistance;
	}
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

void Monster::setAnimate(std::string animateName, bool isLoop)
{
	Ogre::Entity* entity;
	entity = (Ogre::Entity*)mNode->getAttachedObject(0);
	mAnimationState = entity->getAnimationState(animateName);
	mAnimationState->setLoop(isLoop);
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

void Monster::setScale( float x, float y, float z )
{
	mNode->scale(x, y, z);
}

void Monster::harmCheck(float timeSinceLastFrame)
{
	/// 先检查地形，更新怪物信息
	checkCellType();
	
	mCheckMethod->bulletHarmCheck(mMonsterState->getBulletState(), mBulletHarmValue, mBulletHarmTime, mBlood, mSpeed, mSpeedTemp, timeSinceLastFrame);
	mCheckMethod->terrainHarmCheck(mMonsterState->getTerrainState(), mTerrainHarmvalue, mBlood, mSpeed, mSpeedTemp, timeSinceLastFrame);
	/// 状态恢复
	stateRecover();
	/// 速度恢复
	if(mMonsterState->getBulletState() != "ice" && mMonsterState->getTerrainState() != SWAMP)
		mCheckMethod->speedRecover(mSpeed, mSpeedTemp);
	/// 判断是否死亡
	//mIsDead = mCheckMethod->checkIsDead(mBlood);
	if (!mIsDead && mCheckMethod->checkIsDead(mBlood))
	{
		mIsDead = true;
		Stage::playSound("../Media/Sound/dead.wav", false);
	}
	/// 根据地形改地图
	changeMazeByTerrain(mMonsterState->getTerrainState());
	/// 改变头顶血量显示
	Billboard* health = mHealthHUD->getBillboard(0);
	float healthPer = mBlood / mMaxBlood;
	float healthLength = healthPer * mHealthHUD->getDefaultWidth();
	health->setDimensions(healthLength, mHealthHUD->getDefaultHeight());
	ColourValue maxHealthCol = ColourValue(0, 0.8f, 0);
	ColourValue minHealthCol = ColourValue(1, 0, 0);
	ColourValue currHealthCol = maxHealthCol * healthPer + minHealthCol * (1 - healthPer);
	health->setColour(currHealthCol);
}

bool Monster::isMonsterDead()
{
	return mIsDead;
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
	/// 判断是否超出地图
	float halfWidth = mMaze->getEntityWidth() * mMapWidth / 2;
	float halfHeight = mMaze->getEntityHeight() * mMapHeight / 2;
	if(mNode->getPosition().x < -halfWidth || mNode->getPosition().x > halfWidth 
		|| mNode->getPosition().z < -halfHeight || mNode->getPosition().z > halfHeight)
	{
		mMonsterState->setTerrainState(FREE);
		return;
	}
	/// cell的临时变量，用来储存现在怪兽所在的cell的指针
	Cell* cellTemp;
	cellTemp = mMaze->getCellByPos(mNode->getPosition());
   /* if(cellTemp == NULL)
		return;*/
	mMonsterState->setTerrainState(cellTemp->getCellType());
	/// 设置地图伤害
	setTerrainHarm(cellTemp->getHarmValue(), 0);
}

void Monster::checkHitBySpecialBullet(std::string bulletSpell, float bulletTime, float bulletHarm, float bulletAppendHarm)
{
	if(mCheckMethod->isAttributeImmune(bulletSpell, mType))    /// 如果属性免疫
	{
		mMonsterState->setBulletState("attributeImmune");
	}
	else if(mCheckMethod->isAttributeRestriction(bulletSpell, mType))  /// 如果属性克制
	{
		mBlood -= bulletHarm * 2;
		mMonsterState->setBulletState(bulletSpell);
		setBulletHarm(bulletAppendHarm, bulletTime);
	}
	else
	{
		mBlood -= bulletHarm;
		mMonsterState->setBulletState(bulletSpell);
		setBulletHarm(bulletAppendHarm, bulletTime);
	}
}

float Monster::distance( Ogre::Vector3 pos1, Ogre::Vector3 pos2 )
{
	float tempX, tempY;
	tempX = pos1[0] - pos2[0];
	tempY = pos1[2] - pos2[2];
	return sqrt((tempX * tempX + tempY * tempY));
}


bool Monster::isHitByBullet( float* bulletPos, float bulletRadius )
{
	float tempX, tempY;
	tempX = bulletPos[0] - mNode->getPosition().x;
	tempY = bulletPos[2] - mNode->getPosition().z;
	if(sqrt((tempX * tempX + tempY * tempY)) < bulletRadius + mRadius)
		return true;
	else 
		return false;
}

bool Monster::notSpecialBullet( std::string bulletSpell )
{
	if(bulletSpell == "normal")
		return true;
	return false;
}

void Monster::checkHitByBullet( float* bulletPos, float bulletHarm, float bulletAppendHarm, float bulletTime, float bulletRadius, std::string bulletSpell )
{
	if(isHitByBullet(bulletPos, bulletRadius))
	{
  		if(notSpecialBullet(bulletSpell))
			mBlood -= bulletHarm;
		else
			checkHitBySpecialBullet(bulletSpell, bulletTime, bulletHarm, bulletAppendHarm);
	}
}

void Monster::makeMap( Cell** cells )
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
		if(cells[i]->getCellType() != WALL)
		{
			map[i / mMapWidth][i % mMapWidth] = CAN_STEP;
		}
		else
		{
			map[i / mMapWidth][i % mMapWidth] = NOT_STEP;
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
	map[pos.y][pos.x] = SET_MARK;
}

void Monster::stepTo( Pos pos )
{
	map[pos.y][pos.x] = HAS_STEP;
}

void Monster::pushPos( Pos pos, stack<CellNode>& st )
{
	Vect vect[8];                       //上下左右4个方向向量
	vect[0].dx = 0;  vect[0].dy = 1;    //vect[0] = {0, 1};
	vect[1].dx = 1;  vect[1].dy = 0;    //vect[1] = {1, 0};
	vect[2].dx = -1; vect[2].dy = 0;    //vect[2] = {-1, 0};
	vect[3].dx = 0;  vect[3].dy = -1;   //vect[3] = {0, -1};
	vect[4].dx = 1;	 vect[4].dy = -1;
	vect[5].dx = -1; vect[5].dy = 1;
	vect[6].dx = 1;	 vect[6].dy = 1;
	vect[7].dx = -1; vect[7].dy = -1;

	//判断在这4个方向向量中哪几个可以步进
	Judge* head = NULL;
	Judge* ptr = NULL;
	Judge* tmp = NULL;
	bool lock = false;
	Pos now;
	int dist;
	for(int i=0; i<4; i++)
	{
		dist = 10;
		now.x = pos.x + vect[i].dx;
		now.y = pos.y + vect[i].dy;
		Pos tt = Pos(5,5);
		
		if(parent.x != 0 || parent.y != 0)
		{
			tt.x = pos.x - parent.x;
			tt.y = pos.y - parent.y;
		}
		if(tt.x == vect[i].dx && tt.y == vect[i].dy)
		{
			dist -= 1;
		}
		//检测当前位置是否越界且可步进
		if(isValid(now))
			if(map[now.y][now.x]==CAN_STEP)
			{
				//对当前节点进行评估
				dist += abs(now.x-finalPos.x) + abs(now.y-finalPos.y);

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
	this->parent = Pos(sour.x + 1, sour.y);
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
				record[temp.self.y][temp.self.x] = temp.pare;
				parent = temp.pare;
			}
			break;
		}
		else
		{
			if(isValid(temp.self))
			{
				markIt(temp.self);
				record[temp.self.y][temp.self.x] = temp.pare;
				parent = temp.pare;
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
		parent = record[parent.y][parent.x];
		if(parent.x==sour.x && parent.y==sour.y)
		{
			success = true;
		}
	}
	path.push_back(fromPos);
	std::reverse(path.begin(),path.end());
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
	return Pos(0,0);

}

void Monster::transPos()
{
	for(auto it = path.begin(); it != path.end(); ++it)
	{
		ogrePath.push_back((mMaze->translatePos(Ogre::Vector3(Real((*it).x), Real(0), Real((*it).y)))));
	}
}

void Monster::destroyItself()
{
	mNode->detachAllObjects();
}

void Monster::changeMazeByTerrain( int terrainType )
{
	switch(terrainType)
	{
	case TRAP: mMaze->setCellFree(mNode->getPosition()); break;
	default: break;
	}
}

void Monster::setTerrainHarm( float harm, float time )
{
	mTerrainHarmvalue = harm;
}

void Monster::setBulletHarm( float harm, float time )
{
	mBulletHarmValue = harm;
	mBulletHarmTime = time;
}

void Monster::stateRecover()
{
	if(mBulletHarmTime < 0 || mBulletHarmTime == 0)
		mMonsterState->setBulletState("normal");
}

Monster* MonsterFactory::createInstance(SceneManager* sceneMgr, Maze* maze, MonsterManager* monsterMgr)
{
	Ogre::SceneNode* monsterNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entity = sceneMgr->createEntity(mParams["mesh"]);
	monsterNode->attachObject(entity);
	Monster* mon;
	mon = new Monster(monsterNode, maze, monsterMgr);
	if (mParams.find("radius") != mParams.end())
		mon->setRadius((float)atof(mParams["radius"].c_str()));

	if (mParams.find("blood") != mParams.end())
	{
		mon->setBlood((float)atof(mParams["blood"].c_str()));
		mon->setMaxBlood(mon->getBlood());
	}

	if (mParams.find("speed") != mParams.end())
		mon->setSpeed((float)atof(mParams["speed"].c_str()));

	if (mParams.find("spell") != mParams.end())
		mon->setType((mParams["spell"].c_str()));

	if (mParams.find("scale") != mParams.end())
	{
		float scale = (float)atof(mParams["scale"].c_str());
		mon->setScale(scale, scale, scale);
	}

	//mon->setScale(2, 2, 2);

	// 创建怪物头顶血条
	BillboardSet* healthHUD = sceneMgr->createBillboardSet();
	healthHUD->setMaterialName("Glass/Billboard");
	healthHUD->setDefaultWidth(100);
	healthHUD->setDefaultHeight(14);
	SceneNode* hudNode = monsterNode->createChildSceneNode();
	hudNode->attachObject(healthHUD);
	/*Billboard* b2 = healthHUD->createBillboard(0, entity->getBoundingBox().getSize().y, 0);
	b2->setColour(ColourValue::Black);*/
	Billboard* b = healthHUD->createBillboard(0, entity->getBoundingBox().getSize().y, 0);
	//b->setColour(ColourValue(0, 0.75f, 0));
	//b->setDimensions(96, 12);
	mon->setHealthHUD(healthHUD);
	return mon;
}

std::string MonsterFactory::getType()
{
	return mType;
}
