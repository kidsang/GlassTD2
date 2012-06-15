#ifndef __Score_h_
#define __Score_h_

#include <string>
#include <vector>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::string;


/// 处理分数，单例
class Score
{
private:
	Score();

public:

	/// 存档的文件名
	static const string ARCHIVE_NAME;

	static Score* getInstance();
	static void destroyInstance();
	
	~Score();

	/// 杀怪会获得分数
	void killMonster();

	/// 过关会获得分数
	void pass();

	/// 答题正确会获得分数
	void correctAnswer();

	/// 获得当前的分数
	int getScore() const;

	/// 获取排行榜
	std::vector<int> getRankingList();

private:
	int mCurrentScore;  // 当前分数
	static Score* instance;
};





#endif