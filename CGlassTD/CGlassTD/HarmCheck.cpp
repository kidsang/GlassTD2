#include "HarmCheck.h"
#include "Maze.h"

void HarmCheck::bulletHarm( float harm, float& blood )
{
	
}


void HarmCheck::fireHarmCheck( float harm, float& time, float& blood, float timeSinceLastFrame )
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

void HarmCheck::iceHarmCheck( float harm, float& time, float& speed, float speedTemp, float timeSinceLastFrame )
{
	/// �������˺�����
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

void HarmCheck::spikeweedHarmCheck( float harm, float& blood, bool isOnSpikeweed, float timeSinceLastFrame )
{
	if(isOnSpikeweed)
		blood -= harm * timeSinceLastFrame;
}

void HarmCheck::swampHarmCheck( float harm, float& speed, float speedTemp, bool isInSwamp )
{
	if(isInSwamp)
		speed = speedTemp * harm;
	else 
		speed = speedTemp;
}

bool HarmCheck::checkIsDead( float blood )
{
	if(blood < 0 || blood == 0)
		return true;
	else 
		return false;
}

