#include "BillboardSprite.h"


BillboardSprite::BillboardSprite(SceneNode* node, BillboardSet* bs, int row, int col, int unitWidth, int unitHeight)
	: mNode(node), mBillboards(bs), mRow(row), mCol(col), mUnitWidth(unitWidth), mUnitHeight(unitHeight),
	mIsFinished(false)
{
	mWidth = row * unitWidth;
	mHeight = col * unitHeight;
	Billboard* b = mBillboards->getBillboard(0);
	if (b)
		b->setTexcoordRect(0, 0, 1 / (float)mRow, 1 / (float)mCol);
}


BillboardSprite::~BillboardSprite(void)
{
	if (mBillboards)
	{
		mBillboards->clear();
		delete mBillboards;
		mBillboards = 0;
	}
	if (mNode)
	{
		mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());
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
