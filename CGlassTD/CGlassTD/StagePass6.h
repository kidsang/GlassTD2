#ifndef StagePass6_h__
#define StagePass6_h__

#include "LevelStage.h"

/// �����س���
class StagePass6 : public LevelStage
{
private:

public:
	/// ���캯��
	/// @param pSceneManager ������������ָ��
	/// @param pStageManager ��̨��������ָ��
	StagePass6(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass6(void);

	virtual void onEdReplayBtnClick( MyGUI::Widget* sender );

	virtual void onEdNextBtnClick( MyGUI::Widget* sender );

};

#endif // StagePass6_h__

