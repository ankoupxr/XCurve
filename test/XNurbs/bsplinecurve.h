#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <point3dw.h>
#include <curveutil.h>>

class BSplineCurve
{
public:

    static Point3dW ComputePointOnCure(int degree, const std::vector<double>& knotVector, double paramT, const std::vector<Point3dW>& controlPoints)
    {
        Point3dW curvePoint;
        int spanIndex = CurveUtil::FindSpan(degree,knotVector,paramT);
        std::vector<double> N = CurveUtil::BasicFunctions(spanIndex,degree,knotVector,paramT);
        for (int i = 0; i <= degree; i++)
        {
            curvePoint += controlPoints[spanIndex - degree + i] * N[i];
        }
        return curvePoint;
    }

    static std::vector<Point3dW> ComputeDerivatives(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<Point3dW>& controlPoints)
    {
        std::vector<Point3dW> derivatives(derivative + 1);

        int du = std::min(derivative, degree);
        int spanIndex = CurveUtil::FindSpan(degree, knotVector, paramT);
        std::vector<std::vector<double>> nders =
            CurveUtil::BasisFunctionsDerivs(spanIndex, degree, du, knotVector, paramT);

        for (int k = 0; k <= du; k++)
        {
            for (unsigned int j = 0; j <= degree; j++)
            {
                derivatives[k] +=  controlPoints[spanIndex - degree + j] * nders[k][j];
            }
        }
        return derivatives;
    }
};

#endif // BSPLINECURVE_H
