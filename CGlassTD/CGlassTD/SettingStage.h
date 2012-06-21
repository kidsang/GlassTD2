#pragma once
#include "stage.h"
class SettingStage : public Stage
{
public:
	SettingStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);

	~SettingStage(void);

	void notifyMouseButtonClick(MyGUI::Widget* _sender);
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
	bool musicFlag;
	bool soundFlag;
	MyGUI::ImageBox* music;
	MyGUI::ImageBox* sound;
	MyGUI::ImageBox* back;
	MyGUI::VectorWidgetPtr mLayout;
};

