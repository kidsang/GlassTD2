#ifndef BillboardSprite_h__
#define BillboardSprite_h__

/**
 * �ļ���BillboardSprite
 * ���ڣ�2012/06/25
 * ���ߣ�kid
 */

#include "Animator.h"
#include "Animatable.h"
#include "Ogre.h"
using namespace Ogre;

class BillboardSprite
{
private:
	BillboardSet* mBillboards;
	Animatalbe<BillboardSprite> mAniMgr;

	int mRow;
	int mCol;
	int mUnitWidth;
	int mUnitHeight;
	int mWidth;
	int mHeight;
public:
	/// ���캯��
	/// @param bs billboard
	/// @param row ÿ�м���
	/// @param col ÿ�м���
	/// @param unitWidth ÿ��Ԫ���
	/// @param unitHeight ÿ��Ԫ�߶�
	BillboardSprite(BillboardSet* bs, int row, int col, int unitWidth, int unitHeight);
	~BillboardSprite(void);

	/// ��Ӷ���
	void addAnimator(Animator<BillboardSprite>* ani);

	/// ���ж���
	void animate( float timeSinceLastFrame, BillboardSprite* object );

public:
	/// ����billboard set
	BillboardSet* getBillboardSet()
	{
		return mBillboards;
	}

	/// ���ض���������
	const Animatalbe<BillboardSprite>& getAnimateManager()
	{
		return mAniMgr;
	}

	/// ����������
	int getRow()
	{
		return mRow;
	}

	/// ����������
	int getCol()
	{
		return mCol;
	}

	/// ����ÿ����λ�Ŀ��
	int getUnitWidth()
	{
		return mUnitWidth;
	}

	/// ����ÿ����λ�ĸ߶�
	int getUnitHeight()
	{
		return mUnitWidth;
	}

	/// ����ͼƬ�ܸ߶�
	int getWidth()
	{
		return mWidth;
	}

	/// ����ͼƬ�ܸ߶�
	int getHeight()
	{
		return mHeight;
	}
};

#endif // BillboardSprite_h__

