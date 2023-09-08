#ifndef CURVEUTIL_H
#define CURVEUTIL_H

#include <vector>

class CurveUtil
{
public:
    static int FindSpan(int degree,std::vector<double>& knotVector, double u);
    static double BasicFunctions(int i,int k,std::vector<double>& knot,double u);
    static std::vector<std::vector<double>> BasisFunctionsDerivs(int spanIndex,int degree,int derivs,const std::vector<double>& knotVector, double paramT);
};

#endif // CURVEUTIL_H