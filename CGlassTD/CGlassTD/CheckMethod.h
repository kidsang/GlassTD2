#ifndef CheckMethod_h__
#define CheckMethod_h__
#include <string>
#include "CellType.h"
class CheckMethod
{
private:
public:
	CheckMethod(){};
	~CheckMethod(){};
	void bulletHarm(float harm, float& blood);
	void fireHarmCheck(float& harm, float& time, float& blood, float timeSinceLastFrame);
	void iceHarmCheck(float& harm, float& time, float& speedPre, float& speedCurrent, float speedTemp, float timeSinceLastFrame);
	void spikeweedHarmCheck(float& harm, float& blood, float timeSinceLastFrame);
	void swampHarmCheck(float& harm, float& speedPre, float& speedCurrent, float speedTemp);
	void caughtByTrapCheck(float& blood);
	void speedRecover(std::string bulletType, int terrainType, float& speedPre, float& speedCurrent, float speedTemp);
	bool checkIsDead(float blood);
	bool isAttributeImmune(std::string type1, std::string type2);
	bool isAttributeRestriction(std::string strongType, std::string weakType);
	void bulletHarmCheck(std::string bulletType, float harm, float& time, float& blood, float& speedPre, float& speedCurrent, float speedTemp, float timeSinceLastFrame);
	void terrainHarmCheck(int terrainType, float harm, float& blood, float& speedPre, float& speedCurrent, float speedTemp, float timeSinceLastFrame);


};



#endif // CheckMethod_h__