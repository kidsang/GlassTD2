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
	void iceHarmCheck(float& harm, float& time, float& speed, float speedTemp, float timeSinceLastFrame);
	void spikeweedHarmCheck(float& harm, float& blood, float timeSinceLastFrame);
	void swampHarmCheck(float& harm, float& speed, float speedTemp);
	void caughtByTrapCheck(float& blood);
	void speedRecover(float& speed, float speedTemp);
	bool checkIsDead(float blood);
	bool isAttributeImmune(std::string type1, std::string type2);
	bool isAttributeRestriction(std::string strongType, std::string weakType);
	void bulletHarmCheck(std::string bulletType, float harm, float& time, float& blood, float& speed, float speedTemp, float timeSinceLastFrame);
	void terrainHarmCheck(int terrainType, float harm, float& blood, float& speed, float speedTemp, float timeSinceLastFrame);


};



#endif // CheckMethod_h__