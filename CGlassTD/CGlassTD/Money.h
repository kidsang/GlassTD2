#ifndef __Money_h_
#define __Money_h_


/// 处理金钱，单例
class Money
{
private:
	Money();

public:

	enum TrapType
	{
		SPIKEWEED, // 地刺
		SWAMP, // 沼泽
		TRAP, // 捕兽夹
	};
	
	/// 获得实例
	static Money* getInstance();
	static void destroyInstance();

	/// 答题正确会获得金钱
	void correctAnswer();

	/// 放置陷阱会失去金钱，如果金钱已经不够返回false，成功返回true
	bool placeTrap(TrapType);

	/// 获取当前金钱数量
	int getAmount() const;

private:
	static Money* instance;
	int mAmount;
};




#endif