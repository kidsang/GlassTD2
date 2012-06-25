#ifndef BillboardSpriteAnimator_h__
#define BillboardSpriteAnimator_h__

/**
 * 文件：BillboardSpriteAnimator
 * 日期：2012/06/25
 * 作者：kid
 */

#include "Animator.h"
#include "BillboardSprite.h"
using namespace Ogre;

class BillboardSpriteAnimator : public Animator<BillboardSprite>
{
private:
	int mCurrRow;
	int mCurrCol;
public:
	BillboardSpriteAnimator(float timeInterval)
		: Animator(timeInterval), mCurrRow(0), mCurrCol(0)
	{

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
