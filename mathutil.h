#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <point3d.h>
#include <point3dw.h>
#include <vector3d.h>

class MathUtil
{
public:
    static int Factorial(unsigned int number);

    static double Binomial(unsigned int number, unsigned int i);

    //static Point3d PointToLine(Point3d S,Vector3d T,Point3d P);

    //static Point3d Intersect3DLines(Point3dW P0,Vector3d T0,Point3dW P2,Vector3d T2);
};

#endif // MATHUTIL_H
