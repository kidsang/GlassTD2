#ifndef MonsterState_h__
#define MonsterState_h__

class MonsterState
{
protected:
	std::string mBulletState;
	int mTerrainState;

public:
	MonsterState()
	{
		mBulletState = "normal";
		mTerrainState = FREE;
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
};
#endif // MonsterState_h__