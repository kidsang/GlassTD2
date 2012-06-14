#ifndef Animator_h__
#define Animator_h__

/**
 * 文件：Animator
 * 日期：2012/06/14
 * 作者：kid
 */

/// 动画模板类
template <typename T>
class Animator
{
	typedef void(*AnimatorCallback)(void);
private:
	/// 两次动画触发的时间间隔，以秒计算
	float mTimeInterval;
	/// 上次动画触发的时间
	float mLastTime;

	/// 动画是否已播放
	bool mIsStarted;
	
public:
	/// 构造函数
	/// @param timInterval 两次动画触发的时间间隔，以秒计算 
	Animator(float timeInterval)
		: mTimeInterval(timeInterval), mLastTime(0), mIsStarted(false)
	{

	}

	virtual ~Animator(void)
	{

	}

	/// 开始一个动画
	void start()
	{
		mIsStarted = true;
	}

	/// 结束一个动画
	void stop()
	{
		mIsStarted = false;
		mLastTime = 0;
	}

	/// 运行动画
	/// @param timeSinceLastFrame 上一帧(游戏循环)持续的时间
	/// @param object 被动画作用的物体
	/// @note 此函数由外部管理类调用，用户不该重载此函数，而应该重载runImpl
	void run(float timeSinceLastFrame, T* object);

	/// 动画的实现
	/// @param timeSinceLastFrame 上一帧(游戏循环)持续的时间
	/// @param object 被动画作用的物体
	virtual void runImpl(float timeSinceLastFrame, T* object) = 0;

};

template <typename T>
void Animator<T>::run(float timeSinceLastFrame, T* object)
{
	if (!mIsStarted)
		return;

	mLastTime += timeSinceLastFrame;
	if (mLastTime < mTimeInterval)
		return;

	runImpl(timeSinceLastFrame, object);

	mLastTime -= mTimeInterval;
}

#endif // Animator_h__

