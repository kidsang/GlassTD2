#include "BillboardSprite.h"


BillboardSprite::BillboardSprite(BillboardSet* bs, int row, int col, int unitWidth, int unitHeight)
	: mBillboards(bs), mRow(row), mCol(col), mUnitWidth(unitWidth), mUnitHeight(unitHeight)
{
	mWidth = row * unitWidth;
	mHeight = col * unitHeight;
}


BillboardSprite::~BillboardSprite(void)
{
	if (mBillboards)
	{
		mBillboards->clear();
		delete mBillboards;
		mBillboards = 0;
	}
}

void BillboardSprite::addAnimator( Animator<BillboardSprite>* ani )
{
	mAniMgr.addAnimator(ani);
}

void BillboardSprite::animate( float timeSinceLastFrame, BillboardSprite* object )
{
	mAniMgr.animate(timeSinceLastFrame, object);
}
