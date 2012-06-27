#ifndef __Money_h_
#define __Money_h_

#include <MyGUI/MyGUI.h>
#include <string>

/// 处理金钱，单例
class Money
{
private:
	Money(MyGUI::Gui* gui);

public:

	enum TrapType
	{
		SPIKEWEED, // 地刺
		SWAMP, // 沼泽
		TRAP, // 捕兽夹
	};
	
	/// 获得实例
	static Money* getInstance();
	static void init(MyGUI::Gui* gui);
	static void destroyInstance();
	
	~Money();
	
	/// 显示金钱
	void display();
	
	/// 取消金钱显示
	void unDisplay();

	/// 答题正确会获得金钱
	void correctAnswer();
	
	/// 打错扣钱
	void wrongAnswer();

	/// 判断金钱是否足以放置某个陷阱
	bool enough(TrapType);

	/// 放置陷阱会失去金钱，如果金钱已经不够返回false，成功返回true
	bool placeTrap(TrapType);

	/// 获取当前金钱数量
	int getAmount() const;
	
	/// 获取当前金钱数量，返回字符串
	std::string getAmountStr() const;

private:
	static Money* instance;
	int mAmount;
	MyGUI::Gui* mGui;
	MyGUI::TextBox* mTextBox;
	MyGUI::ImageBox* mImageBox;
};




#endif