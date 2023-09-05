#include "curveutil.h"

int CurveUtil::FindSpan(int degree, std::vector<double>& knotVector, double u)
{
    int n = knotVector.size() - degree - 2;

    int low = degree;
    int high = n + 1;
    int mid = static_cast<int>(floor((low+high)/2.0));

    while(u < knotVector[mid] || u >= knotVector[mid+1])
    {
        if(u < knotVector[mid])
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
        mid = (low + high) / 2;
    }
    return(mid);
}


double CurveUtil::BasicFunctions(int i,int k,std::vector<double>& knot,double u)
{
    double x1,x2,y1,y2;
    x1=0;x2=0;y1=0;y2=0;
    if (k==0)									//若阶数为1
    {
        if ((u>knot[i])&&(u<=knot[i+1]))		//若参数u落在[ui,ui+1]节点区间内
            return 1;
        else
            return 0;
    }
    else if(k>0)								//若阶数大于1
    {
        if (knot[i+k]!=knot[i])					//若ui+k-1与ui为非重节点
        {
            x1=BasicFunctions(i,k-1,knot,u);
            x2=(u-knot[i])*x1/(knot[i+k]-knot[i]);	//计算B样条基函数递归定义的第一项
        } else if(knot[i+k]==knot[i])
            x2=0;
        if (knot[i+k+1]!=knot[i+1])
        {
            y1=BasicFunctions(i+1,k-1,knot,u);
            y2=(knot[i+k+1]-u)*y1/(knot[i+k+1]-knot[i+1]);//计算B样条基函数递归定义的第二项
        }
        else if(knot[i+k+1]==knot[i+1])
            y2=0;
        return x2+y2;						//计算B样条基函数递归定义的第一项和第二项之和
    }
    return 1;
}


std::vector<std::vector<double>> CurveUtil::BasisFunctionsDerivs(int spanIndex, int degree,  int derivative, const std::vector<double>& knotVector, double paramT)
{
    std::vector<std::vector<double>> derivatives(derivative + 1, std::vector<double>(degree + 1));
    std::vector<std::vector<double>> ndu(degree + 1,std::vector<double>(degree + 1));

    ndu[0][0] = 1.0;

    std::vector<double> left(degree + 1);
    std::vector<double> right(degree + 1);

    double saved = 0.0;
    double temp = 0.0;

    for (int j = 1; j <= degree; j++)
    {
        left[j] = paramT - knotVector[spanIndex + 1 - j];
        right[j] = knotVector[spanIndex + j] - paramT;

        saved = 0.0;
        for (int r = 0; r < j; r++)
        {
            ndu[j][r] = right[r + 1] + left[j - r];
            temp = ndu[r][j - 1] / ndu[j][r];

            ndu[r][j] = saved + right[r + 1] * temp;
            saved = left[j - r] * temp;
        }
        ndu[j][j] = saved;
    }

    for (int j = 0; j <= degree; j++)
    {
        derivatives[0][j] = ndu[j][degree];
    }

    std::vector<std::vector<double>> a(2,std::vector<double>(degree + 1));
    for (int r = 0; r <= degree; r++)
    {
        int s1 = 0;
        int s2 = 1;
        a[0][0] = 1.0;

        for (int k = 1; k <= derivative; k++)
        {
            double d = 0.0;
            int rk = r - k;
            int pk = degree - k;

            if (r >= k)
            {
                a[s2][0] = a[s1][0] / ndu[pk + 1][rk];
                d = a[s2][0] * ndu[rk][pk];
            }

            int j1 = 0;
            int j2 = 0;

            if (rk >= -1)
                j1 = 1;
            else
                j1 = -rk;

            if (r - 1 <= pk)
                j2 = k - 1;
            else
                j2 = degree - r;

            for (int j = j1; j <= j2; j++)
            {
                a[s2][j] = (a[s1][j] - a[s1][j - 1]) / ndu[pk + 1][rk + j];
                d += a[s2][j] * ndu[rk + j][pk];
            }
            if (r <= pk)
            {
                a[s2][k] = -a[s1][k - 1] / ndu[pk + 1][r];
                d += a[s2][k] * ndu[r][pk];
            }
            derivatives[k][r] = d;

            int temp = s1;
            s1 = s2;
            s2 = temp;
        }
    }

    int r = degree;
    for (int k = 1; k <= derivative; k++)
    {
        for (int j = 0; j <= degree; j++)
        {
            derivatives[k][j] *= r;
        }
        r *= degree - k;
    }
    return derivatives;
}
