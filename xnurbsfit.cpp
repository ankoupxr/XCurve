
#include "xnurbsfit.h"



xnurbscurve XNurbsFit::GlobalInterpolationCurve(std::vector<Point3d> points,int n,int k)
{
    std::vector<double> uk = CurveUtil::GetUkByThroughPoints(points);
    std::vector<double> U = CurveUtil::GetKnotVectorByThroughPoints(k,n+1,uk);
    std::vector<std::vector<double>> A(n+1);
    for(int i = 0;i <= n;i++)
    {
        A[i].resize(n+1,0.0);
        int spanIndex = CurveUtil::FindSpan(k,U,uk[i]);
        std::vector<double> BValues = CurveUtil::BasisFunctions(U[i],spanIndex,k,U);
        for (int j = 0; j < k; j++)
        {
            A[i][spanIndex-k+j] = BValues[j];
        }
    }
    std::vector<std::vector<double>> UpperMat;
    std::vector<std::vector<double>> LowMat;
    MathUtil::LUDecomposition(A,UpperMat,LowMat);

    std::vector<Point3dW> ControlPoints(points.size());

    for (int i = 0; i < 3; i++)
    {
        std::vector<double> rhs;
        for (int j = 0; j  <= n; j++ )
        {
            if(i == 0)
            {
                rhs[j] = points[j].GetX();
            }
            if(i == 1)
            {
                rhs[j] = points[j].GetY();
            }
            if(i == 2)
            {
                rhs[j] = points[j].GetZ();
            }
        }
        std::vector<double> sol;
        MathUtil::ForwardBackward(A,UpperMat,LowMat,rhs,sol);

        for (int j = 0; j <= n; j++)
        {
            if(i == 0)
            {
                ControlPoints[j].SetX(sol[j]);
            }
            if(i == 1)
            {
                ControlPoints[j].SetY(sol[j]);
            }
            if(i == 2)
            {
                ControlPoints[j].SetZ(sol[j]);
            }
            ControlPoints[j].SetW(1);
        }
    }

    xnurbscurve xc(ControlPoints,U,k);
    return xc;
}
