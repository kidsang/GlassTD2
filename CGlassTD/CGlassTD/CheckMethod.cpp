#include "CheckMethod.h"

void CheckMethod::bulletHarm( float harm, float& blood )
{
	
}


void CheckMethod::fireHarmCheck( float& harm, float& time, float& blood, float timeSinceLastFrame )
{
	
	/// �������˺�����
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
	/// �������˺�����
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

void CheckMethod::spikeweedHarmCheck( float& harm, float& blood, bool isOnSpikeweed, float timeSinceLastFrame )
{
	if(isOnSpikeweed)
		blood -= harm * timeSinceLastFrame;
}

void CheckMethod::swampHarmCheck( float& harm, float& speed, float speedTemp, bool isInSwamp )
{
	if(isInSwamp)
		speed = speedTemp * harm;
}

bool CheckMethod::checkIsDead( float blood )
{
	if(blood < 0.0f || blood == 0.0f)
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

void CheckMethod::caughtByTrapCheck( float& blood, bool isCaught )
{
	if(isCaught)
		blood = 0.0f;
}

void CheckMethod::speedRecover( float& speed, float speedTemp )
{
	speed = speedTemp;
}

