
#ifndef __GamgeResource_h__
#define __GamgeResource_h__

#include "OgreString.h"


class GameResource
{
public:
	static Ogre::String WORD_OF_STAGE[6];
	static Ogre::String WORD_RESULT_SUCCESS;
	static Ogre::String WORD_RESULT_FAIL;
	static Ogre::String WORD_RESULT_PAUSE;
	GameResource(void);
	~GameResource(void);
};



#endif