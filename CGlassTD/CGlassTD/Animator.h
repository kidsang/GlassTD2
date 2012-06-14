#ifndef Animator_h__
#define Animator_h__

/**
 * 文件：Animator
 * 日期：2012/06/14
 * 作者：kid
 */

#include <vector>

/// 动画模板类
template <typename T>
class Animator
{
	typedef void(*AnimatorCallback)(T* object);
	typedef std::vector<AnimatorCallback> CallbackList;
private:
	/// 两次动画触发的时间间隔，以秒计算
	float mTimeInterval;
	/// 上次动画触发的时间
	float mLastTime;

	/// 动画是否已播放
	bool mIsStarted;

	/// 在start时执行的回调函数列表
	CallbackList mOnStartCallbacks;
	/// 在stop时执行的回调函数列表
	CallbackList mOnStopCallbacks;
	
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

	/// 增加一个on start回调函数
	/// @param cb on start 回调函数
	void addOnStartCallback(AnimatorCallback cb)
	{
		mOnStartCallbacks.push_back(cb);
	}

	/// 移除一个on start回调函数
	/// @param cb on start 回调函数
	void removeOnStartCallback(AnimatorCallback cb)
	{
		auto iter = std::find(mOnStartCallbacks.begin(), mOnStartCallbacks.end(), cb);
		if (iter != mOnStartCallbacks.end())
			mOnStartCallbacks.erase(iter);
	}

	/// 增加一个on stop回调函数
	/// @param cb on stop 回调函数
	void addOnStopCallback(AnimatorCallback cb)
	{
		mOnStopCallbacks.push_back(cb);
	}

	/// 移除一个on stop回调函数
	/// @param cb on stop 回调函数
	void removeOnStopCallback(AnimatorCallback cb)
	{
		auto iter = std::find(mOnStopCallbacks.begin(), mOnStopCallbacks.end(), cb);
		if (iter != mOnStopCallbacks.end())
			mOnStopCallbacks.erase(iter);
	}

	/// 开始一个动画
	void start(T* object)
	{
		mIsStarted = true;
		for (auto iter = mOnStartCallbacks.begin(); iter != mOnStartCallbacks.end(); ++iter)
			(*iter)(object);
	}

	/// 结束一个动画
	void stop(T* object)
	{
		mIsStarted = false;
		mLastTime = 0;
		for (auto iter = mOnStopCallbacks.begin(); iter != mOnStopCallbacks.end(); ++iter)
			(*iter)(object);
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

