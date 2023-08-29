#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <point3d.h>

template <typename T>
class BSplineCurve
{
public:
    BSplineCurve();

private:
    std::vector<std::vector<Point3d>> m_controlPoints;
    std::vector<T> knotVector;
    double paramT;
    int n,k;
};

#endif // BSPLINECURVE_H
