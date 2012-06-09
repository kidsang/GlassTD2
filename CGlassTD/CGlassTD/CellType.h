
#ifndef __CellType_h_
#define __CellType_h_
/// Cell ������
/// @member WALL ǽ
/// @member SWAMP ����
/// @member SPIKEWEED ���޼� 
/// @member THORM ���� 
/// @member FREE �յ� 
/// @member SHASOW_SWAMP ����Ӱ������
/// @member SHASOW_SPIKEWEED ����Ӱ�Ĳ��޼�
/// @member SHASOW_THORM ����Ӱ�ľ���

enum CellType
{
	WALL,SWAMP,SPIKEWEED,THORM,FREE,SHADOW_SWAMP,SHADOW_SPIKEWEED,SHADOW_THORM
};
#endif