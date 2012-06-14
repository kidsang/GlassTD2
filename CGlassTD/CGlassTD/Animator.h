#ifndef Animator_h__
#define Animator_h__

/**
 * �ļ���Animator
 * ���ڣ�2012/06/14
 * ���ߣ�kid
 */

/// ����ģ����
template <typename T>
class Animator
{
	typedef void(*AnimatorCallback)(void);
private:
	/// ���ζ���������ʱ�������������
	float mTimeInterval;
	/// �ϴζ���������ʱ��
	float mLastTime;

	/// �����Ƿ��Ѳ���
	bool mIsStarted;
	
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

	/// ��ʼһ������
	void start()
	{
		mIsStarted = true;
	}

	/// ����һ������
	void stop()
	{
		mIsStarted = false;
		mLastTime = 0;
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

