
#ifndef __Monster_h_
#define __Monster_h_

#include "BaseApplication.h"
#include "ObjectFactory.h"
#include "Common.h"
#include "CheckMethod.h"
#include "Maze.h"
#include <stack>
using namespace Ogre;

class Cell;


const float FULL_BLOOD = 100.0f;
const float BEGIN_POS_X = -100.0f;
const float BEGIN_POS_Y = 0.f;
const float BEGIN_POS_Z = -100.f;
const float FIRE_HARM_TIME = 1.0f;    ///火属性伤害持续时间
const float ICE_HARM_TIME = 1.0f;     /// 冰属性伤害持续时间
const float ICE_HARM_SPEED = 0.4f;    /// 冰属性影响的速度值
const float FIRE_HARM_BLOOD = 0.01f;  /// 火属性伤害的血量值
const float SPIKEWEED_HARM_BLOOD = 20.0f;  /// 地刺伤害的血量值
const float SWAMP_HARM_SPEED = 0.4f;  /// 沼泽影响的速度值


struct Pos
{
	int x;
	int y;
	Pos(int x1, int y1)
	{
		x = x1;
		y = y1;
	}
	Pos(){}
};

struct CellNode
{
	Pos pare;
	Pos self;
	int dist;
};

struct Judge
{
	CellNode node;
	Judge* next;
};

struct Vect
{
	int dx;
	int dy;
};


struct HarmList
{
	/// 冰属性伤害
	float iceHarm;
	/// 冰属性伤害持续时间
	float iceHarmTime;
	/// 火属性伤害
	float fireHarm;
	/// 火属性伤害持续时间
	float fireHarmTime;

	/// 是否被捕兽器捉到
	bool beCaught;
	/// 地刺伤害
	float spikeweedHarm;
	/// 是否站在地刺上
	bool isOnSpikeweed;
	/// 沼泽伤害
	float swampHarm;
	/// 是否在沼泽里
	bool isInSwamp;

	HarmList()
		:iceHarm(0), 
		fireHarm(0),
		spikeweedHarm(SPIKEWEED_HARM_BLOOD),
		swampHarm(SWAMP_HARM_SPEED),
		isOnSpikeweed(false),
		beCaught(false),
		isInSwamp(false),
		iceHarmTime(ICE_HARM_TIME),
		fireHarmTime(FIRE_HARM_TIME){};
};

class Monster
{
protected:
	int mBeginPosIndex;
	int mNextPosIndex;
	Ogre::Vector3 mBeginPos;
	Ogre::Vector3 mNextPos;
	/// 怪兽的速度
	float mSpeed;
	/// 怪兽的速度备份，以便还原速度
	float mSpeedTemp;
	/// 怪物的血量
	float mBlood;
	/// 怪物的面向（一个三维向量)
	Ogre::Vector3 mFace;
	/// 怪物的种类
	std::string mType;
	Ogre::SceneNode* mNode;
	Ogre::String mMesh;
	Ogre::AnimationState* mAnimationState;
	/// 怪兽的半径范围
	float mRadius;
	/// 伤害列表
	HarmList mHarmList;
	/// 怪兽是否死亡
    bool mIsDead;
	/// 伤害检测类
	CheckMethod* mCheckMethod;
	/// 怪物与下一个目的坐标的距离
	float mDistance;
   /* /// 用于测试用
	int j ;*/
	std::vector<std::vector<Ogre::Vector3>> mMonsterPaths;
public:
	Monster(){}
	Monster(SceneNode* node);
	Monster(SceneNode* node, Maze* maze);
	//Monster(SceneNode* node, Maze* maze);
	Monster(Ogre::SceneManager* sceneMgr, Ogre::SceneNode* parentNode);
	~Monster(void);
	void go(float timeSinceLastFrame);
	float getBlood(void);
	void setBlood(int mBlood);
	std::string getType(void);
	Ogre::Vector3 getFace(void);
	void setFace(Ogre::Vector3& mFace);
	Ogre::String getMesh();
	void setMesh(Ogre::String mesh);
	void setType(std::string type);
	void setSpeed(float speed);
	void setRadius(float radius);
	///两点之间的距离
	float distance(Ogre::Vector3 pos1, Ogre::Vector3 pos2);
	/// 设置动画
	void setAnimate();
	/// 根据时间刷新动画状态
	void addTimeToAnimation(float timeSinceLastFrame);
	/// 获取怪兽的半径
	float getRadius();
	/// 缩放怪物
	void monsterScale(float x, float y, float z);
	/// 伤害检测
	void harmCheck(float timeSinceLastFrame);
	/// 怪兽死掉
	bool isMonsterDead();
	/// 检查被炮弹集中
	void checkHitByBullet(float* bulletPos, float bulletHarm, float bulletAppendHarm, float bulletTime, float bulletRadius, std::string bulletSpell);
	/// 毁灭自己，将绑定的模型去掉
	void destroyItself();
private:
	/// 地图指针
	Maze* mMaze;
	/// 地图的二维数组
	int** map;
	/// 地图的宽
	int mMapWidth;
	/// 地图的高
	int mMapHeight;
	/// 终点的坐标
	Pos finalPos;
	/// 入口坐标
	std::vector<Pos> startPos;
	/// 怪兽要走的路径
	std::vector<Pos> path;
	std::vector<Ogre::Vector3> ogrePath;
	/// 构造寻路地图
	void makeMap(Cell* cells);
	/// 判定坐标是否有效
	/// @param pos 要判定的坐标
	/// @return 返回true表示有效，反之无效
	bool isValid(Pos pos);
	/// 判定坐标是否是终点坐标
	bool isFinal(Pos pos);
	void markIt(Pos pos);
	void stepTo(Pos pos);
	void pushPos(Pos pos, std::stack<CellNode>& st);
	bool findPath(Pos sour);
	Pos getStep();
	void transPos();

	/// 设置怪兽收到的火属性伤害
	void setHitByFire(float harm, float time);
	/// 设置怪兽收到的冰属性伤害
	void setHitByIce(float harm, float time);
	/// 设置怪兽收到的火属性伤害
	void setNotHitByFire();
	/// 设置怪兽收到的冰属性伤害
	void setNotHitByIce();
	/// 设置被捕兽器捉住
	void setBeCaughtByTrap();
	/// 设置在地刺上
	void setInsideSpikeweed();
	/// 设置在地刺外
	void setOutsideSpikeweed();
	/// 设置在沼泽里
	void setInsideSwamp();
	/// 设置在沼泽外
	void setOutsideSwamp();
	/// 检查怪兽所在的cell的类型，根据类型修改参数
	void checkCellType();
	///检查被特殊炮弹集中
	void checkHitBySpecialBullet(std::string bulletSpell, float bulletTime, float bulletHarm, float bulletAppendHarm);
	///是否被炮弹击中
	bool isHitByBullet(float* bulletPos, float bulletRadius);
	bool notSpecialBullet(std::string bulletSpell);

};


class MonsterFactory
{
	NameValueList mParams;
	std::string mType;

public:
	MonsterFactory(NameValueList params)
		:mParams(params)
	{
		mType = params["spell"];
	}
	~MonsterFactory()
	{

	}

	Monster* createInstance(SceneManager* sceneMgr);
	Monster* createInstance(SceneManager* sceneMgr, Maze* maze);
	
	std::string getType();
};

#endif // Monster_h__
