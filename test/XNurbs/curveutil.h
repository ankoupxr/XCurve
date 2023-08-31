#ifndef CURVEUTIL_H
#define CURVEUTIL_H

#include <vector>

class CurveUtil
{
public:
    static int FindSpan(int degree,const std::vector<double>& knotVector, double u);
    static std::vector<double> BasicFunctions(int spanIndex,int degree,const std::vector<double>& knotVector,double t);
    static std::vector<double> AllBasicFunctions(int spanIndex,int degree,const std::vector<double>& knotVector,double t);
};

#endif // CURVEUTIL_H
