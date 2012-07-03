#ifndef __LifeStage_h__
#define __LifeStage_h__

#include "LevelStage.h"

/// ����ģʽ����
class LifeStage : public LevelStage
{
private:

public:
	/// ���캯��
	/// @param pSceneManager ������������ָ��
	/// @param pStageManager ��̨��������ָ��
	LifeStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~LifeStage(void);

	virtual void onEdReplayBtnClick( MyGUI::Widget* sender );

	virtual void onEdNextBtnClick( MyGUI::Widget* sender );

};

#endif // LifeStage_h__

