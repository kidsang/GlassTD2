
#ifndef __CellType_h_
#define __CellType_h_
/// Cell 的类型
/// @member WALL 墙
/// @member SWAMP 沼泽
/// @member SPIKEWEED 捕兽夹 
/// @member THORM 荆刺 
/// @member FREE 空地 
/// @member SHASOW_SWAMP 有阴影的沼泽
/// @member SHASOW_SPIKEWEED 有阴影的捕兽夹
/// @member SHASOW_THORM 有阴影的荆刺

enum CellType
{
	WALL,SWAMP,SPIKEWEED,THORM,FREE,SHADOW_SWAMP,SHADOW_SPIKEWEED,SHADOW_THORM
};
#endif