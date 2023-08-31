#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <point3d.h>
#include <curveutil.h>>

template <typename T>
class BSplineCurve
{
public:
    template<typename T>
    static T ComputePointOnCure(int degree, const std::vector<double>& knotVector, double paramT, const std::vector<T>& controlPoints)
    {
        T curvePoint;
        int spanIndex = CurveUtil::FindSpan(degree,knotVector,paramT);
        std::vector<double> N = CurveUtil::BasicFunctions(spanIndex,degree,knotVector,paramT);
        for (int i = 0; i <= degree; i++)
        {
            curvePoint += N[i] * controlPoints[spanIndex - degree + i];
        }
        return curvePoint;
    }

};

#endif // BSPLINECURVE_H
