#ifndef QuestBank_h__
#define QuestBank_h__

/**
 * 文件：QuestBank
 * 日期：2012/06/14
 * 作者：kid
 */

#include "ParamParser.h"
#include <time.h>

/// 单条问题
class Quest
{
public:
	typedef std::map<std::string, std::string> Selections;
	
private:
	/// 问题
	std::string mQuestion;
	/// 选项列表
	Selections mSelections;
	/// 正确答案编号
	std::string mAnswer;

public:
	/// 获取问题
	const std::string& getQuestion()
	{
		return mQuestion;
	}

	/// 设置问题
	void setQuestion(const std::string& question)
	{
		mQuestion = question;
	}

	/// 获取答案编号
	const std::string& getAnswer()
	{
		return mAnswer;
	}

	/// 设置答案编号
	void setAnswer(const std::string& answer)
	{
		mAnswer = answer;
	}

	/// 增加选项
	/// @param id 选项编号
	/// @param selection 选项内容
	void addSelection(std::string id, std::string selection)
	{
		mSelections.insert(std::make_pair(id, selection));
	}

	/// 获取选项列表
	const Selections& getSelections()
	{
		return mSelections;
	}
};

/// 问题集
class QuestBank
{
	typedef std::vector<Quest*> Quests;

private:
	/// 题目列表
	Quests mQuests;

public:

	~QuestBank();

	/// 向题库增加题集
	/// @param filePath 题集文件路径
	void addQuests(const std::string& filePath);

	/// 随机获取一条题目
	Quest* getQuest()
	{
		return mQuests[clock() % mQuests.size()];
	}

	/// 随机获取n条题目
	/// @param num 要获取的题目数量
	std::vector<Quest*> getQuests(unsigned int num);

	/// 调试用，输出所有题目
	void debugPrint();
};

#endif // QuestBank_h__

