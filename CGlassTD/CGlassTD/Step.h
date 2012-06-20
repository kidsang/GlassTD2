#ifndef __Step_h_
#define __Step_h_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

/// �ؿ�LevelStage����Ҫ�Ĳ��裬ͬ���ؿ������в��蹲�����ݣ�������Ϊ��ͬ
/// @author: LiaoNanhao
class Step
{
public:
	virtual ~Step()
	{

	}

	/// ��ʼ�����������������ͷλ�õ�
	virtual void init() = 0;

	/// �����������߼�
	/// @param timeSinceLastFrame ����һ֡���������ŵ�ʱ��
	/// @note �������ÿһ֡���ã��������ÿһ֡���߼�
	virtual bool run(float timeSinceLastFrame) = 0;

	// ���¼�����Ӧ
	/// ���¼��̴����˺���
	/// @param arg �¼�����Ϣ
	virtual bool onKeyPressed(const OIS::KeyEvent &arg) = 0;

	/// ����ƶ������˺���
	/// @param arg �¼�����Ϣ
	virtual bool onMouseMoved(const OIS::MouseEvent &arg) = 0;

	/// ������괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	virtual bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	/// �ͷ���괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	virtual bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
};


#endif