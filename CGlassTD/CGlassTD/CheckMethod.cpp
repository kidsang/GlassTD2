#include "CheckMethod.h"

void CheckMethod::bulletHarm( float harm, float& blood )
{
	
}


void CheckMethod::fireHarmCheck( float harm, float& time, float& blood, float timeSinceLastFrame )
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

void CheckMethod::iceHarmCheck( float harm, float& time, float& speed, float speedTemp, float timeSinceLastFrame )
{
	/// 冰属性伤害运作
	if(harm != 0 && time > 0)
	{
		speed = speedTemp * harm;
		time -= timeSinceLastFrame;
	}
	else if(time < 0 || time == 0)
	{
		speed = speedTemp;
		harm = 0;
	}
}

void CheckMethod::spikeweedHarmCheck( float harm, float& blood, bool isOnSpikeweed, float timeSinceLastFrame )
{
	if(isOnSpikeweed)
		blood -= harm * timeSinceLastFrame;
}

void CheckMethod::swampHarmCheck( float harm, float& speed, float speedTemp, bool isInSwamp )
{
	if(isInSwamp)
		speed = speedTemp * harm;
	else 
		speed = speedTemp;
}

bool CheckMethod::checkIsDead( float blood )
{
	if(blood < 0 || blood == 0)
		return true;
	else 
		return false;
}

bool CheckMethod::isAttributeImmune( std::string type1, std::string type2 )
{
	if(type1 == type2)
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

