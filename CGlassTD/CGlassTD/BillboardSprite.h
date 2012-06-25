#ifndef BillboardSprite_h__
#define BillboardSprite_h__

/**
 * 文件：BillboardSprite
 * 日期：2012/06/25
 * 作者：kid
 */

#include "Animator.h"
#include "Animatable.h"
#include "Ogre.h"
using namespace Ogre;

class BillboardSprite
{
private:
	BillboardSet* mBillboards;
	SceneNode* mNode;
	Animatalbe<BillboardSprite> mAniMgr;

	int mRow;
	int mCol;
	int mUnitWidth;
	int mUnitHeight;
	int mWidth;
	int mHeight;

	bool mIsFinished;
public:
	/// 构造函数
	/// @param bs billboard
	/// @param row 每行几个
	/// @param col 每列几个
	/// @param unitWidth 每单元宽度
	/// @param unitHeight 每单元高度
	BillboardSprite(SceneNode* node, BillboardSet* bs, int row, int col, int unitWidth, int unitHeight);
	~BillboardSprite(void);

	/// 添加动画
	void addAnimator(Animator<BillboardSprite>* ani);

	/// 运行动画
	void animate( float timeSinceLastFrame, BillboardSprite* object );

public:
	void setFinish(bool isFinished)
	{
		mIsFinished = isFinished;
	}

	bool getFinish()
	{
		return mIsFinished;
	}

	/// 返回billboard set
	BillboardSet* getBillboardSet()
	{
		return mBillboards;
	}

	/// 返回动画管理器
	const Animatalbe<BillboardSprite>& getAnimateManager()
	{
		return mAniMgr;
	}

	/// 返回总行数
	int getRow()
	{
		return mRow;
	}

	/// 返回总列数
	int getCol()
	{
		return mCol;
	}

	/// 返回每个单位的宽度
	int getUnitWidth()
	{
		return mUnitWidth;
	}

	/// 返回每个单位的高度
	int getUnitHeight()
	{
		return mUnitWidth;
	}

	/// 返回图片总高度
	int getWidth()
	{
		return mWidth;
	}

	/// 返回图片总高度
	int getHeight()
	{
		return mHeight;
	}
};

#endif // BillboardSprite_h__

