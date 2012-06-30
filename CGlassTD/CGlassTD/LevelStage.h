#ifndef __LevelStage_h_
#define __LevelStage_h_

#include <vector>
using std::vector;
#include "Stage.h"
#include "Step.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"
#include "Animator.h"
#include "Money.h"

class LevelStage : public Stage
{
private:
	int mLevel;
	String* mWallType;
	bool mKeyboardControl;
	bool quitFlag;
public:
	/// 构造函数
	LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui, int level);

	/// 析构函数
	virtual ~LevelStage();

	/// 获取当前关卡
	int getLevel();

	bool getQuitFlag()
	{
		return quitFlag;
	}
	bool getKeyboardController();
	/// 跳到第i个步骤
	void jumpToStep(Step* step);

	/// 场景的运行逻辑
	/// @param timeSinceLastFrame 从上一帧到现在流逝的时间
	/// @note 这个函数每一帧调用，处理的是每一帧的逻辑
	/// @note 应该只由框架调用
	bool run(float timeSinceLastFrame);

	// 对事件的响应
	/// 按下键盘触发此函数
	/// @param arg 事件的信息
	/// @note 应该只由框架调用
	bool onKeyPressed(const OIS::KeyEvent &arg);

	/// 鼠标移动触发此函数
	/// @param arg 事件的信息
	/// @note 应该只由框架调用
	bool onMouseMoved(const OIS::MouseEvent &arg);

	/// 按下鼠标触发此函数
	/// @param arg 事件的信息
	/// @param id 哪个按键
	/// @note 应该只由框架调用
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/// 释放鼠标触发此函数
	/// @param arg 事件的信息
	/// @param id 哪个按键
	/// @note 应该只由框架调用
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/// 添加一个摄像机动画
	void addCameraAnimator(Animator<Ogre::Camera>* ani)
	{
		mCameraAnimatorList.push_back(ani);
	}
	///创建放置物体的UI界面
	void createGUI0();

	///创建发射炮弹的UI界面
	void createGUI1();

	///更新炮弹数
	void updateCount();

	///更新炮弹图片
	void updateImage();

	///场景转换时切换UI
	void change0to1();
	void change1to0();

	///
	// Get/Set
public:
	bool isRunning()
	{
		return mIsRunning;
	}

	bool isEnd()
	{
		return mIsEnd;
	}

	void setEnd(bool isEnd)
	{
		mIsEnd = isEnd;
	}

	void setRunning(bool isRunning)
	{
		mIsRunning = isRunning;
	}

	Cannon* getCannon()
	{
		return mCannon;
	}

	Maze* getMaze()
	{
		return mMaze;
	}

	UFO* getUFO()
	{
		return mUFO;
	}

	MonsterManager* getMonsterManager()
	{
		return mMonsterManager;
	}

	BulletManager* getBulletManager()
	{
		return mBulletManager;
	}

	const Vector3& getGravity()
	{
		return mGravity;
	}

	void setGravity(const Vector3& gravity)
	{
		mGravity = gravity;
	}

	// helper functions
	MyGUI::VectorWidgetPtr getLevelStageLayout()
	{
		return levelStageLayout;
	}


protected:
	/// 初始化大炮
	/// @param cannonDefine 大炮定义xml文件
	/// @param bulletDefine 炮弹定义xml文件
	void initializeCannon(const std::string& cannonDefine, const std::string& bulletDefine);

	/// 初始化迷宫
	/// @param mazeDefine 迷宫定义xml文件
	/// @param cellDefine 墙定义xml文件
	void initializeMaze(const std::string& mazeDefine, const std::string& cellDefine);

	/// 初始化UFO
	/// @param ufoDefine UFO定义xml文件
	void initializeUFO(const std::string& ufoDefine);

	
protected:
	/// 当前的分场景
	Step* mCurrentStep;
	/// 炮
	Cannon* mCannon;
	/// 迷宫
	Maze* mMaze;
	/// UFO
	UFO* mUFO;
	/// 怪物序列管理器
	MonsterManager* mMonsterManager;

	/// 炮弹管理类
	BulletManager* mBulletManager;
	/// 摄像机动画列表
	std::deque<Animator<Ogre::Camera>*> mCameraAnimatorList;

	/// 环境重力
	Vector3 mGravity;
	/// 场景是否在运行
	bool mIsRunning;
	
	// 游戏是否结束
	bool mIsEnd;

	/// 平行光
	Light* mLight;

	///GUI
public:
	MyGUI::VectorWidgetPtr levelStageLayout;

	static const int cellCount = 3;
	static const int cellSize = 80;
	MyGUI::ImageBox* cellImage[cellCount];
	
	static const int imageCount = 3; 
	static const int imageSize = 40;
	MyGUI::ImageBox* bulletImage[imageCount];
	MyGUI::TextBox* bulletCount[imageCount];

	/// 显示Esc弹出菜单
	void showEscMenu();
	/// 注销显示Esc菜单
	void unShowEscMenu();
	/// 结束画面根
	MyGUI::VectorWidgetPtr mEdLayout;
	// 结束画面回调函数

	/// Esc画面根
	MyGUI::VectorWidgetPtr mEdEscLayout;
protected:
	/// 回主菜单
	void onEdHomeBtnClick(MyGUI::Widget* sender);

	/// 重玩
	/// @note 该方法需要由场景分别实现，因为特定场景才知道需要重玩哪个场景
	virtual void onEdReplayBtnClick(MyGUI::Widget* sender) = 0;

	/// 下一关
	/// @note 该方法需要由场景分别实现，因为特定场景才知道需要跳到哪个场景
	virtual void onEdNextBtnClick(MyGUI::Widget* sender) = 0;

	void onEdBackToMenuBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdBackToMenuBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdReplayBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdReplayBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdNextBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdNextBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscBackToMenuBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscBackToMenuBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscResumeBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscResumeBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscExitBtnPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void onEdEscExitBtnRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
};


#endif