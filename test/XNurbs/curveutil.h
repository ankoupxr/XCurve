#ifndef CURVEUTIL_H
#define CURVEUTIL_H

#include <vector>

class CurveUtil
{
public:
    static int FindSpan(int degree,std::vector<double>& knotVector, double u);
};

#endif // CURVEUTIL_H
