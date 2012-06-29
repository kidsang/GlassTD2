#ifndef __Sound_h__
#define __Sound_h__

#include <irrKlang.h>

/// ������Ϸ��Ч������
class Sound
{
private:
	Sound();
	static Sound* instance;
public:
	static Sound* getInstance();
	static void destroy();

public:
	~Sound();
	void play(const char* fileName, bool loop);
	void stop();

private:
	irrklang::ISoundEngine* mEngine;
};


#endif