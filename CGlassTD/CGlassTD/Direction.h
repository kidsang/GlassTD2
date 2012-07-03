#ifndef __Direction_h_
#define __Direction_h_

/// 弃之不用的类
class Direction
{
public:
	Direction(double x = 0.0, double y = 0.0, double z = 0.0);
	~Direction(void);

public:
	double mX;
	double mY;
	double mZ;
};


#endif