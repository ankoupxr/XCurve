#ifndef CURVEUTIL_H
#define CURVEUTIL_H

#include <vector>

class CurveUtil
{
public:
    static int FindSpan(int degree,std::vector<double>& knotVector, double u);
    static double BasicFunctions(double t,int i,int k,std::vector<double>& T);
    static std::vector<std::vector<double>> BasisFunctionsDerivs(int spanIndex,int degree,int derivs,const std::vector<double>& knotVector, double paramT);
};

#endif // CURVEUTIL_H
