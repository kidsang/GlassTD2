#include "Sound.h"


Sound* Sound::instance = 0;

Sound::Sound()
{
	mEngine = irrklang::createIrrKlangDevice();
}
Sound::~Sound()
{
	if (mEngine != 0) mEngine->drop();
}

Sound* Sound::getInstance()
{
	if (instance == 0) instance = new Sound();

	return instance;
}

void Sound::destroy()
{
	if (instance != 0) delete instance;
}

void Sound::play(const char* fileName, bool loop)
{
	mEngine->play2D(fileName, loop);
}

void Sound::stop()
{
	mEngine->stopAllSounds();
}