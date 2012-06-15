#ifndef __Money_h_
#define __Money_h_


/// �����Ǯ������
class Money
{
private:
	Money();

public:

	enum TrapType
	{
		SPIKEWEED, // �ش�
		SWAMP, // ����
		TRAP, // ���޼�
	};
	
	/// ���ʵ��
	static Money* getInstance();
	static void destroyInstance();

	/// ������ȷ���ý�Ǯ
	void correctAnswer();

	/// ���������ʧȥ��Ǯ�������Ǯ�Ѿ���������false���ɹ�����true
	bool placeTrap(TrapType);

	/// ��ȡ��ǰ��Ǯ����
	int getAmount() const;

private:
	static Money* instance;
	int mAmount;
};




#endif