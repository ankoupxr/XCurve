#ifndef CURVEUTIL_H
#define CURVEUTIL_H

#include <mathutil.h>
#include <vector>
#include <point3dw.h>

class CurveUtil
{
public:
    static int FindSpan(int degree,std::vector<double>& knotVector, double u);
    static double BasicFunctions(double t,int i,int k,std::vector<double>& T);
    static void GetKnotVector(std::vector<double>& T,std::vector<std::vector<Point3dW>> m_controlPoints,int nCount,int num,int k, bool bU);//通过Hartley-Judd计算
    static std::vector<double> BasisFunctions(double t,int i,int k,std::vector<double>& T);
    static std::vector<std::vector<double>> BasisFunctionsDerivs(int spanIndex,
                                                                 int degree,int derivs,
                                                                 const std::vector<double>& knotVector, double paramT);
    static std::vector<double> GetUkByThroughPoints(const std::vector<Point3d> throughPoints);
    static std::vector<double> GetKnotVectorByThroughPoints(int k,int pointsCount,const std::vector<double> _uk);
};

#endif // CURVEUTIL_H
