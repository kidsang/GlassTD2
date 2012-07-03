#ifndef MonsterState_h__
#define MonsterState_h__

/// 定义了怪物当前所受的状态，如冰冻、燃烧等
class MonsterState
{
protected:
	std::string mBulletState;
	std::string mBulletStatePre;
	int mTerrainState;
	int mTerrainStatePre;

public:
	MonsterState()
	{
		mBulletState = "normal";
		mBulletStatePre = "normal";
		mTerrainState = FREE;
		mTerrainStatePre = FREE;
	}
	~MonsterState()
	{

	}
	std::string getBulletState()
	{
		return mBulletState;
	}
	void setBulletState(std::string state)
	{
		mBulletState = state;
	}
	int getTerrainState()
	{
		return mTerrainState;
	}
	void setTerrainState(int state)
	{
		mTerrainState = state;
	}
	std::string getBulletStatePre()
	{
		return mBulletStatePre;
	}
	void setBulletStatePre(std::string state)
	{
		mBulletStatePre = state;
	}
	int getTerrainStatePre()
	{
		return mTerrainStatePre;
	}
	void setTerrainStatePre(int state)
	{
		mTerrainStatePre = state;
	}
};
#endif // MonsterState_h__