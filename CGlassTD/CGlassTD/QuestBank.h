#ifndef QuestBank_h__
#define QuestBank_h__

/**
 * �ļ���QuestBank
 * ���ڣ�2012/06/14
 * ���ߣ�kid
 */

#include "ParamParser.h"
#include <time.h>

/// ��������
class Quest
{
public:
	typedef std::map<std::string, std::string> Selections;
	
private:
	/// ����
	std::string mQuestion;
	/// ѡ���б�
	Selections mSelections;
	/// ��ȷ�𰸱��
	std::string mAnswer;

public:
	/// ��ȡ����
	const std::string& getQuestion()
	{
		return mQuestion;
	}

	/// ��������
	void setQuestion(const std::string& question)
	{
		mQuestion = question;
	}

	/// ��ȡ�𰸱��
	const std::string& getAnswer()
	{
		return mAnswer;
	}

	/// ���ô𰸱��
	void setAnswer(const std::string& answer)
	{
		mAnswer = answer;
	}

	/// ����ѡ��
	/// @param id ѡ����
	/// @param selection ѡ������
	void addSelection(std::string id, std::string selection)
	{
		mSelections.insert(std::make_pair(id, selection));
	}

	/// ��ȡѡ���б�
	const Selections& getSelections()
	{
		return mSelections;
	}
};

/// ���⼯
class QuestBank
{
	typedef std::vector<Quest*> Quests;

private:
	/// ��Ŀ�б�
	Quests mQuests;

public:

	~QuestBank();

	/// ����������⼯
	/// @param filePath �⼯�ļ�·��
	void addQuests(const std::string& filePath);

	/// �����ȡһ����Ŀ
	Quest* getQuest()
	{
		return mQuests[clock() % mQuests.size()];
	}

	/// �����ȡn����Ŀ
	/// @param num Ҫ��ȡ����Ŀ����
	std::vector<Quest*> getQuests(unsigned int num);

	/// �����ã����������Ŀ
	void debugPrint();
};

#endif // QuestBank_h__

