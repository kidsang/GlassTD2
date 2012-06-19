#include "QuestBank.h"


void QuestBank::debugPrint()
{
	/*for (auto iter = mQuests.begin(); iter != mQuests.end(); ++iter)
	{
		Quest* q = (*iter);
		cout << q->getQuestion() << endl;
		std::map<std::string, std::string> s = q->getSelections();
		for (auto siter = s.begin(); siter != s.end(); ++siter)
			cout << (*siter).first << "." << (*siter).second << "  ";
		cout << endl << endl;
	}*/
}

std::vector<Quest*> QuestBank::getQuests( unsigned int num )
{
	std::vector<Quest*> out;
	int base = clock();
	for (unsigned int i=0; i<num; i++)
		out.push_back(mQuests[(base + i * 1234) % mQuests.size()]);
	return out;
}

void QuestBank::addQuests( const std::string& filePath )
{
	ParamParser p = ParamParser(filePath);
	p.parse();
	p.moveToFirst();
	while (p.hasNext())
	{
		NameValueList* nvl = p.getNext();
		Quest* q = new Quest();
		q->setQuestion((*nvl)["q"]);
		q->setAnswer((*nvl)["ans"]);
		q->addSelection("a", (*nvl)["a"]);
		q->addSelection("b", (*nvl)["b"]);
		q->addSelection("c", (*nvl)["c"]);
		q->addSelection("d", (*nvl)["d"]);
		mQuests.push_back(q);
	}
}

QuestBank::~QuestBank()
{
	// «Âø’Ã‚ø‚
	for (auto iter = mQuests.begin(); iter != mQuests.end(); ++iter)
		delete (*iter);
}
