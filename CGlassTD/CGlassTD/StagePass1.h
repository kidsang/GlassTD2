#ifndef StagePass1_h__
#define StagePass1_h__

#include "LevelStage.h"

/// ��һ�س���
class StagePass1 : public LevelStage
{
private:


public:
	/// ���캯��
	/// @param pSceneManager ������������ָ��
	/// @param pStageManager ��̨��������ָ��
	StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass1(void);
};

#endif // StagePass1_h__

