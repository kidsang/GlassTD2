#ifndef __Cell_h_
#define __Cell_h_

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "ObjectFactory.h"
#include "CellType.h"
using namespace std;
using namespace Ogre;


class Cell
{
private:
	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode* mParentNode;
	/// �˿ռ��λ������
	Ogre::Vector2* pPos;
	/// �˿ռ��ʵ��ָ��
	Entity* mEntity;
	/// �˿ռ�ĳ����ڵ�
	SceneNode* mSceneNode;
	/// �˿ռ������
	CellType mType;
	/// �˺�ֵ 
	float mHarmValue;

public:
	Cell(void);
	/// Cell��Ĺ��캯��֮һ
	/// @param sceneManager ������ָ��
	/// @param parentNode �����ĸ��ڵ�ָ��
	/// @param state �˿ռ�ĵ�ǰ��������
	/// @param maxContain �˿ռ�������������
	/// @param pos �˿ռ������ֵ����
	Cell(Ogre::SceneManager* sceneManager,Ogre::SceneNode* parentNode,Ogre::String mesh,Ogre::Vector2* pos,CellType type, float harmValue);
	Cell(Ogre::SceneManager* sceneManager,Ogre::SceneNode* parentNode,Ogre::String mesh,Ogre::Vector2* pos,int type, float harmValue);
	/// ���캯��
	/// @param pos �˿ռ������ֵ����
	Cell(Ogre::SceneManager* sceneManager,Ogre::SceneNode* parentNode,Ogre::Vector2* pos);
	~Cell(void);
	/// ��ȡ�ռ������
	CellType getCellType();
	/// ���ÿռ�����
	bool setCellType(CellType type, Ogre::String mesh, float harmValue);
	bool setCellType(CellType type);
	/// ��ȡ�ռ�ĸ߶�
	float getHeight();
	/// ��ȡ�˺�ֵ
	float getHarmValue();
};

#endif

