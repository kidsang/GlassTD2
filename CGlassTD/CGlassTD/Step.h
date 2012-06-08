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
	/// �����������߼�
	/// @param timeSinceLastFrame ����һ֡���������ŵ�ʱ��
	/// @note �������ÿһ֡���ã��������ÿһ֡���߼�
	virtual void run(float timeSinceLastFrame) = 0;

	// ���¼�����Ӧ
	/// ���¼��̴����˺���
	/// @param arg �¼�����Ϣ
	virtual void onKeyPressed(const OIS::KeyEvent &arg) = 0;

	/// ����ƶ������˺���
	/// @param arg �¼�����Ϣ
	virtual void onMouseMoved(const OIS::MouseEvent &arg) = 0;

	/// ������괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	virtual void onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	/// �ͷ���괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	virtual void onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
};


#endif