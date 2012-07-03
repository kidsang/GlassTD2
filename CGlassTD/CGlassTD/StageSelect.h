

#ifndef __StageSelect_h__
#define __StageSelect_h__

#include "Stage.h"

/// ��Ϸ���˵�����
class StageSelect: public Stage
{
public:
	StageSelect(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);

	~StageSelect();

	void notifyMouseButtonMove(MyGUI::Widget* _sender, int _left, int _top);

	void notifyMouseButtonPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);

	void notifyMouseButtonRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	/// �����������߼�
	/// @param timeSinceLastFrame ����һ֡���������ŵ�ʱ��
	/// @note �������ÿһ֡���ã��������ÿһ֡���߼�
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool run(float timeSinceLastFrame);

	// ���¼�����Ӧ
	/// ���¼��̴����˺���
	/// @param arg �¼�����Ϣ
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onKeyPressed(const OIS::KeyEvent &arg);

	/// ����ƶ������˺���
	/// @param arg �¼�����Ϣ
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onMouseMoved(const OIS::MouseEvent &arg);

	/// ������괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/// �ͷ���괥���˺���
	/// @param arg �¼�����Ϣ
	/// @param id �ĸ�����
	/// @note Ӧ��ֻ�ɿ�ܵ���
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
private:
	MyGUI::ImageBox* stageBG;
	MyGUI::ImageBox* stage1Btn;
	MyGUI::ImageBox* stage2Btn;
	MyGUI::ImageBox* stage3Btn;
	MyGUI::ImageBox* stage4Btn;
	MyGUI::ImageBox* stage5Btn;
	MyGUI::ImageBox* stage6Btn;
	MyGUI::ImageBox* backBtn;
	MyGUI::VectorWidgetPtr mLayout;
	int preFlag;
	int flag;
};

#endif

