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

    static Point3d PointToLine(Point3d S,Vector3d T,Point3d P);

    static Point3d Intersect3DLines(Point3d P0,Vector3d T0,Point3d P2,Vector3d T2);

    static bool IsAlmostEqualTo(double value1, double value2, double tolerance = 1E-6);

    static bool IsNaN(double value);
};

#endif // MATHUTIL_H
