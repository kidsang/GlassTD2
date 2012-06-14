#ifndef Animator_h__
#define Animator_h__

/**
 * �ļ���Animator
 * ���ڣ�2012/06/14
 * ���ߣ�kid
 */

#include <vector>

/// ����ģ����
template <typename T>
class Animator
{
	typedef void(*AnimatorCallback)(T* object);
	typedef std::vector<AnimatorCallback> CallbackList;
private:
	/// ���ζ���������ʱ�������������
	float mTimeInterval;
	/// �ϴζ���������ʱ��
	float mLastTime;

	/// �����Ƿ��Ѳ���
	bool mIsStarted;

	/// ��startʱִ�еĻص������б�
	CallbackList mOnStartCallbacks;
	/// ��stopʱִ�еĻص������б�
	CallbackList mOnStopCallbacks;
	
public:
	/// ���캯��
	/// @param timInterval ���ζ���������ʱ������������� 
	Animator(float timeInterval)
		: mTimeInterval(timeInterval), mLastTime(0), mIsStarted(false)
	{

	}

	virtual ~Animator(void)
	{

	}

	/// ����һ��on start�ص�����
	/// @param cb on start �ص�����
	void addOnStartCallback(AnimatorCallback cb)
	{
		mOnStartCallbacks.push_back(cb);
	}

	/// �Ƴ�һ��on start�ص�����
	/// @param cb on start �ص�����
	void removeOnStartCallback(AnimatorCallback cb)
	{
		auto iter = std::find(mOnStartCallbacks.begin(), mOnStartCallbacks.end(), cb);
		if (iter != mOnStartCallbacks.end())
			mOnStartCallbacks.erase(iter);
	}

	/// ����һ��on stop�ص�����
	/// @param cb on stop �ص�����
	void addOnStopCallback(AnimatorCallback cb)
	{
		mOnStopCallbacks.push_back(cb);
	}

	/// �Ƴ�һ��on stop�ص�����
	/// @param cb on stop �ص�����
	void removeOnStopCallback(AnimatorCallback cb)
	{
		auto iter = std::find(mOnStopCallbacks.begin(), mOnStopCallbacks.end(), cb);
		if (iter != mOnStopCallbacks.end())
			mOnStopCallbacks.erase(iter);
	}

	/// ��ʼһ������
	void start(T* object)
	{
		mIsStarted = true;
		for (auto iter = mOnStartCallbacks.begin(); iter != mOnStartCallbacks.end(); ++iter)
			(*iter)(object);
	}

	/// ����һ������
	void stop(T* object)
	{
		mIsStarted = false;
		mLastTime = 0;
		for (auto iter = mOnStopCallbacks.begin(); iter != mOnStopCallbacks.end(); ++iter)
			(*iter)(object);
	}

	/// ���ж���
	/// @param timeSinceLastFrame ��һ֡(��Ϸѭ��)������ʱ��
	/// @param object ���������õ�����
	/// @note �˺������ⲿ��������ã��û��������ش˺�������Ӧ������runImpl
	void run(float timeSinceLastFrame, T* object);

	/// ������ʵ��
	/// @param timeSinceLastFrame ��һ֡(��Ϸѭ��)������ʱ��
	/// @param object ���������õ�����
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

