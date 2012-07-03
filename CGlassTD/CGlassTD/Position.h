#ifndef __Position_h_
#define __Position_h_

/// 弃之不用的类
class Position
{
private :
	int mX;
	int mZ;
public:
	Position(void);
	Position(int x, int z);
	~Position(void);
	int getX();
	int getZ();
	void setX(int x);
	void setZ(int z);
};

#endif

