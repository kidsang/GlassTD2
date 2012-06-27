#ifndef __Money_h_
#define __Money_h_

#include <MyGUI/MyGUI.h>
#include <string>

/// �����Ǯ������
class Money
{
private:
	Money(MyGUI::Gui* gui);

public:

	enum TrapType
	{
		SPIKEWEED, // �ش�
		SWAMP, // ����
		TRAP, // ���޼�
	};
	
	/// ���ʵ��
	static Money* getInstance();
	static void init(MyGUI::Gui* gui);
	static void destroyInstance();
	
	~Money();
	
	/// ��ʾ��Ǯ
	void display();
	
	/// ȡ����Ǯ��ʾ
	void unDisplay();

	/// ������ȷ���ý�Ǯ
	void correctAnswer();
	
	/// ����Ǯ
	void wrongAnswer();

	/// �жϽ�Ǯ�Ƿ����Է���ĳ������
	bool enough(TrapType);

	/// ���������ʧȥ��Ǯ�������Ǯ�Ѿ���������false���ɹ�����true
	bool placeTrap(TrapType);

	/// ��ȡ��ǰ��Ǯ����
	int getAmount() const;
	
	/// ��ȡ��ǰ��Ǯ�����������ַ���
	std::string getAmountStr() const;

private:
	static Money* instance;
	int mAmount;
	MyGUI::Gui* mGui;
	MyGUI::TextBox* mTextBox;
	MyGUI::ImageBox* mImageBox;
};




#endif