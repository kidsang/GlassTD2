#ifndef __Score_h_
#define __Score_h_

#include <string>
#include <vector>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::string;


/// �������������
class Score
{
private:
	Score();

public:

	/// �浵���ļ���
	static const string ARCHIVE_NAME;

	static Score* getInstance();
	static void destroyInstance();
	
	~Score();

	/// ɱ�ֻ��÷���
	void killMonster();

	/// ���ػ��÷���
	void pass();

	/// ������ȷ���÷���
	void correctAnswer();

	/// ��õ�ǰ�ķ���
	int getScore() const;

	/// ��ȡ���а�
	std::vector<int> getRankingList();

private:
	int mCurrentScore;  // ��ǰ����
	static Score* instance;
};





#endif