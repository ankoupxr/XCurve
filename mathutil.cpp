#include "mathutil.h"

int MathUtil::Factorial(unsigned int number)
{
    if (number == 0)
        return 1;
    else
        return number * Factorial(number - 1);
}

double MathUtil::Binomial(unsigned int number, unsigned int i)
{
    return Factorial(number) / (Factorial(i) * Factorial(number - 1));
}

Point3d MathUtil::PointToLine(Point3d S,Vector3d T,Point3d P)
{
    Vector3d V = P - S;
    Vector3d N = T / T.Norm();
    double D = V.dot(N);
    Point3d Q = S + N * D;
    return Q;
}

Point3d MathUtil::Intersect3DLines(Point3d P0,Vector3d T0,Point3d P2,Vector3d T2)
{
    Vector3d P0P2 = P2 - P0;
    Vector3d crossT0T2 = T0.cross(T2);
    Vector3d crossP0T2 = P0P2.cross(T2);

    double denominator = crossT0T2.dot(crossT0T2);

    if (denominator < 1e-6) {
        // 两条直线平行或重合，无交点
        return Point3d(NAN, NAN, NAN);
    }

    double t = crossP0T2.dot(crossT0T2) / denominator;
    Point3d intersection = P0 + T0 * t;

    return intersection;
}
