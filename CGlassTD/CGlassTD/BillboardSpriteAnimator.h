#ifndef BillboardSpriteAnimator_h__
#define BillboardSpriteAnimator_h__

/**
 * �ļ���BillboardSpriteAnimator
 * ���ڣ�2012/06/25
 * ���ߣ�kid
 */

#include "Animator.h"
#include "BillboardSprite.h"
using namespace Ogre;

void DestoryExplodeSprite(BillboardSprite* bs)
{
	bs->setFinish(true);
}

/// ���鶯��
/// ����ĳ��ʱ���������Ŷ���
/// ͨ�����ϸı������������ʵ��
class BillboardSpriteAnimator : public Animator<BillboardSprite>
{
private:
	int mCurrRow;
	int mCurrCol;
public:
	BillboardSpriteAnimator(float timeInterval)
		: Animator(timeInterval), mCurrRow(0), mCurrCol(0)
	{
		this->addOnStopCallback(DestoryExplodeSprite);
	}

	virtual void runImpl( float timeSinceLastFrame, BillboardSprite* object ) 
	{
		BillboardSet* bs = object->getBillboardSet();
		int count = bs->getNumBillboards();
		for (int i=0; i<count; ++i)
		{
			Billboard* b = bs->getBillboard(i);
			b->setTexcoordRect(
				mCurrRow / (Ogre::Real)object->getRow(),
				mCurrCol / (Ogre::Real)object->getCol(),
				(mCurrRow + 1) / (Ogre::Real)object->getRow(),
				(mCurrCol + 1) / (Ogre::Real)object->getCol()
				);
		}

		mCurrRow++;
		if (mCurrRow == object->getRow())
		{
			mCurrRow = 0;
			mCurrCol++;
			if (mCurrCol == object->getCol())
				this->stop(object);
		}
	}

};

#endif // BillboardSpriteAnimator_h__
