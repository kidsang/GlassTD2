
#ifndef __CellType_h_
#define __CellType_h_
/// Cell 的类型
/// @member WALL 墙
/// @member SWAMP 沼泽
/// @member SPIKEWEED 地刺 
/// @member TRAP 捕兽夹 
/// @member FREE 空地 
/// @member SHASOW_SWAMP 有阴影的沼泽
/// @member SHASOW_SPIKEWEED 有阴影的捕兽夹
/// @member SHASOW_THORM 有阴影的荆刺

enum CellType
{
	WALL,SWAMP,SPIKEWEED,TRAP,FREE,SHADOW_SWAMP,SHADOW_SPIKEWEED,SHADOW_TRAP
};
#endif