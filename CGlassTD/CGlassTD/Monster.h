
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
const float FIRE_HARM_TIME = 1.0f;    ///�������˺�����ʱ��
const float ICE_HARM_TIME = 1.0f;     /// �������˺�����ʱ��
const float ICE_HARM_SPEED = 0.4f;    /// ������Ӱ����ٶ�ֵ
const float FIRE_HARM_BLOOD = 0.01f;  /// �������˺���Ѫ��ֵ
const float SPIKEWEED_HARM_BLOOD = 20.0f;  /// �ش��˺���Ѫ��ֵ
const float SWAMP_HARM_SPEED = 0.4f;  /// ����Ӱ����ٶ�ֵ


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
	/// �������˺�
	float iceHarm;
	/// �������˺�����ʱ��
	float iceHarmTime;
	/// �������˺�
	float fireHarm;
	/// �������˺�����ʱ��
	float fireHarmTime;

	/// �Ƿ񱻲�����׽��
	bool beCaught;
	/// �ش��˺�
	float spikeweedHarm;
	/// �Ƿ�վ�ڵش���
	bool isOnSpikeweed;
	/// �����˺�
	float swampHarm;
	/// �Ƿ���������
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
	/// ���޵��ٶ�
	float mSpeed;
	/// ���޵��ٶȱ��ݣ��Ա㻹ԭ�ٶ�
	float mSpeedTemp;
	/// �����Ѫ��
	float mBlood;
	/// ���������һ����ά����)
	Ogre::Vector3 mFace;
	/// ���������
	std::string mType;
	Ogre::SceneNode* mNode;
	Ogre::String mMesh;
	Ogre::AnimationState* mAnimationState;
	/// ���޵İ뾶��Χ
	float mRadius;
	/// �˺��б�
	HarmList mHarmList;
	/// �����Ƿ�����
    bool mIsDead;
	/// �˺������
	CheckMethod* mCheckMethod;
	/// ��������һ��Ŀ������ľ���
	float mDistance;
   /* /// ���ڲ�����
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
	///����֮��ľ���
	float distance(Ogre::Vector3 pos1, Ogre::Vector3 pos2);
	/// ���ö���
	void setAnimate();
	/// ����ʱ��ˢ�¶���״̬
	void addTimeToAnimation(float timeSinceLastFrame);
	/// ��ȡ���޵İ뾶
	float getRadius();
	/// ���Ź���
	void monsterScale(float x, float y, float z);
	/// �˺����
	void harmCheck(float timeSinceLastFrame);
	/// ��������
	bool isMonsterDead();
	/// ��鱻�ڵ�����
	void checkHitByBullet(float* bulletPos, float bulletHarm, float bulletAppendHarm, float bulletTime, float bulletRadius, std::string bulletSpell);
	/// �����Լ������󶨵�ģ��ȥ��
	void destroyItself();
private:
	/// ��ͼָ��
	Maze* mMaze;
	/// ��ͼ�Ķ�ά����
	int** map;
	/// ��ͼ�Ŀ�
	int mMapWidth;
	/// ��ͼ�ĸ�
	int mMapHeight;
	/// �յ������
	Pos finalPos;
	/// �������
	std::vector<Pos> startPos;
	/// ����Ҫ�ߵ�·��
	std::vector<Pos> path;
	std::vector<Ogre::Vector3> ogrePath;
	/// ����Ѱ·��ͼ
	void makeMap(Cell* cells);
	/// �ж������Ƿ���Ч
	/// @param pos Ҫ�ж�������
	/// @return ����true��ʾ��Ч����֮��Ч
	bool isValid(Pos pos);
	/// �ж������Ƿ����յ�����
	bool isFinal(Pos pos);
	void markIt(Pos pos);
	void stepTo(Pos pos);
	void pushPos(Pos pos, std::stack<CellNode>& st);
	bool findPath(Pos sour);
	Pos getStep();
	void transPos();

	/// ���ù����յ��Ļ������˺�
	void setHitByFire(float harm, float time);
	/// ���ù����յ��ı������˺�
	void setHitByIce(float harm, float time);
	/// ���ù����յ��Ļ������˺�
	void setNotHitByFire();
	/// ���ù����յ��ı������˺�
	void setNotHitByIce();
	/// ���ñ�������׽ס
	void setBeCaughtByTrap();
	/// �����ڵش���
	void setInsideSpikeweed();
	/// �����ڵش���
	void setOutsideSpikeweed();
	/// ������������
	void setInsideSwamp();
	/// ������������
	void setOutsideSwamp();
	/// ���������ڵ�cell�����ͣ����������޸Ĳ���
	void checkCellType();
	///��鱻�����ڵ�����
	void checkHitBySpecialBullet(std::string bulletSpell, float bulletTime, float bulletHarm, float bulletAppendHarm);
	///�Ƿ��ڵ�����
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
