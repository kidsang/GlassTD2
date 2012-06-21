#include "CheckMethod.h"

void CheckMethod::bulletHarm( float harm, float& blood )
{
	
}


void CheckMethod::fireHarmCheck( float& harm, float& time, float& blood, float timeSinceLastFrame )
{
	
	/// 火属性伤害运作
	if(harm != 0 && time > 0)
	{
		blood -= harm * timeSinceLastFrame;
		time -= timeSinceLastFrame;
	}
	else 
		harm = 0;
}

void CheckMethod::iceHarmCheck( float& harm, float& time, float& speed, float speedTemp, float timeSinceLastFrame )
{
	/// 冰属性伤害运作
	if(harm != 0 && time > 0)
	{
		speed = speedTemp * harm;
		time -= timeSinceLastFrame;
	}
	else
	{
		harm = 0;
	}
}

void CheckMethod::spikeweedHarmCheck( float& harm, float& blood, float timeSinceLastFrame )
{
	blood -= harm * timeSinceLastFrame;
}

void CheckMethod::swampHarmCheck( float& harm, float& speed, float speedTemp )
{
	speed = speedTemp * harm;
}

bool CheckMethod::checkIsDead( float blood )
{
	return (blood <= 0);
}

bool CheckMethod::isAttributeImmune( std::string type1, std::string type2 )
{
	if(type1 == type2 && type1 != "normal")
		return true;
	return false;
}

bool CheckMethod::isAttributeRestriction( std::string strongType, std::string weakType )
{
	if(strongType == "fire" && weakType == "ice")
		return true;

	if(strongType == "ice" && weakType == "fire")
		return true;

	return false;
}

void CheckMethod::caughtByTrapCheck( float& blood )
{
	blood = 0.0f;
}

void CheckMethod::speedRecover( float& speed, float speedTemp )
{
	speed = speedTemp;
}

void CheckMethod::bulletHarmCheck( std::string bulletType, float harm, float& time, float& blood, float& speed, float speedTemp, float timeSinceLastFrame )
{
	if(bulletType == "normal" || bulletType == "attributeImmune")
	{
		return;
	}
	if(bulletType == "ice")
	{
		iceHarmCheck(harm, time, speed, speedTemp, timeSinceLastFrame);
	}
	if(bulletType == "fire")
	{
		fireHarmCheck(harm, time, blood, timeSinceLastFrame);
	}
}

void CheckMethod::terrainHarmCheck( int terrainType, float harm, float& blood, float& speed, float speedTemp, float timeSinceLastFrame )
{
	switch(terrainType)
	{
	case FREE: return;
	case SPIKEWEED: spikeweedHarmCheck(harm, blood, timeSinceLastFrame); break;
	case SWAMP: swampHarmCheck(harm, speed, speedTemp); break;
	case TRAP: caughtByTrapCheck(blood); break;
	default: break;
	}
}

