#include "Score.h"

const string Score::ARCHIVE_NAME = "save.dat";
Score* Score::instance = 0;

Score::Score() : mCurrentScore(0)
{
}

Score* Score::getInstance()
{
	if (instance == 0)
	{
		instance = new Score();
	}
	return instance;
}

void Score::destroyInstance()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

Score::~Score()
{
	ofstream fout;
	fout.open(Score::ARCHIVE_NAME, std::ios::app);
	fout<<mCurrentScore<<std::endl;
	fout.close();
}


void Score::killMonster()
{
	mCurrentScore += 2;
}

void Score::pass()
{
	mCurrentScore += 10;
}

void Score::correctAnswer()
{
	mCurrentScore += 5;
}

int Score::getScore() const
{
	return mCurrentScore;
}


std::vector<int> getRankingList()
{
	ifstream fin;
	fin.open(Score::ARCHIVE_NAME, std::ios::in);
	int buffer;
	std::vector<int> rankingList;
	rankingList.clear();
	while (fin>>buffer)
	{
		rankingList.push_back(buffer);
	}
	fin.close();

	return rankingList;
}

