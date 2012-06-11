
#ifndef __CellType_h_
#define __CellType_h_
/// Cell ������
/// @member WALL ǽ
/// @member SWAMP ����
/// @member SPIKEWEED �ش� 
/// @member TRAP ���޼� 
/// @member FREE �յ� 
/// @member SHASOW_SWAMP ����Ӱ������
/// @member SHASOW_SPIKEWEED ����Ӱ�Ĳ��޼�
/// @member SHASOW_THORM ����Ӱ�ľ���

enum CellType
{
	WALL,SWAMP,SPIKEWEED,TRAP,FREE,SHADOW_SWAMP,SHADOW_SPIKEWEED,SHADOW_TRAP
};
#endif