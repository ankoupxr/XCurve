#include "curveutil.h"

int CurveUtil::FindSpan(int degree, std::vector<double>& knotVector, double u)
{
    int n = knotVector.size() - degree - 2;

    if (MathUtil::IsAlmostEqualTo(u, knotVector[n + 1]))
    {
        return n;
    }

    int low = degree;
    int high = n + 1;
    int mid = (low+high)/2.0;

    while (u < knotVector[mid] ||
           u>= knotVector[mid + 1])
    {
        if (u < knotVector[mid])
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
        mid = (low + high) / 2.0;
    }
    return mid;
}


void CurveUtil::GetKnotVector(std::vector<double>& T,std::vector<std::vector<Point3dW>> m_controlPoints,int nCount,int num,int k, bool bU)
{
    //小于等于曲线次数k的节点值为0
    for(int i = 0;i <= k;i++)
    {
        T[i] = 0.0;
    }
    //大于n的节点值为1
    for(int i = num+1;i <= num + k + 1;i++)
    {
        T[i] = 1.0;
    }
    //计算其他节点值
    for(int i = k+1;i <= num; i++)
    {
        double sum = 0.0;
        for(int j = k + 1;j <= i;j++)
        {
            double numerator = 0.0;//计算分子
            for (int loop = j - k;loop  <= j-1; loop++)
            {
                if(bU)//选择计算节点矢量U还是计算节点矢量V
                    numerator+=(m_controlPoints[nCount][loop].GetX()-m_controlPoints[nCount][loop-1].GetX())*
                                     (m_controlPoints[nCount][loop].GetX()-m_controlPoints[nCount][loop-1].GetX())
                                 +(m_controlPoints[nCount][loop].GetY()-m_controlPoints[nCount][loop-1].GetY())*
                                       (m_controlPoints[nCount][loop].GetY()-m_controlPoints[nCount][loop-1].GetY());
                else
                    numerator+=(m_controlPoints[loop][nCount].GetX()-m_controlPoints[loop-1][nCount].GetX())*
                                     (m_controlPoints[loop][nCount].GetX()-m_controlPoints[loop-1][nCount].GetX())
                                 +(m_controlPoints[loop][nCount].GetY()-m_controlPoints[loop-1][nCount].GetY())*
                                       (m_controlPoints[loop][nCount].GetY()-m_controlPoints[loop-1][nCount].GetY());
            }
            double denominator = 0.0;//计算分母
            for(int loop1 = k+1;loop1 <= num+1;loop1++)
            {
                for (int loop2 = loop1 - k;loop2 <= loop1 - 1;loop2++)
                {
                    if(bU)
                    {
                        denominator+=(m_controlPoints[nCount][loop2].GetX()-m_controlPoints[nCount][loop2-1].GetX())*
                                           (m_controlPoints[nCount][loop2].GetX()-m_controlPoints[nCount][loop2-1].GetX())
                                       +(m_controlPoints[nCount][loop2].GetY()-m_controlPoints[nCount][loop2-1].GetY())*
                                             (m_controlPoints[nCount][loop2].GetY()-m_controlPoints[nCount][loop2-1].GetY());
                    }
                    else
                    {
                        denominator+=(m_controlPoints[loop2][nCount].GetX()-m_controlPoints[loop2-1][nCount].GetX())*
                                           (m_controlPoints[loop2][nCount].GetX()-m_controlPoints[loop2-1][nCount].GetX())+
                                       (m_controlPoints[loop2][nCount].GetY()-m_controlPoints[loop2-1][nCount].GetY())*
                                           (m_controlPoints[loop2][nCount].GetY()-m_controlPoints[loop2-1][nCount].GetY());
                    }
                }
            }
            sum+=numerator/denominator;
        }
        T[i] = sum;
    }

}

double CurveUtil::BasicFunctions(double t,int i,int k,std::vector<double>& T)
{
    double value1,value2,value;
    if(k==0)
    {
        if(t>=T[i] && t<T[i+1])
            return 1.0;
        else
            return 0.0;
    }
    if(k>0)
    {
        if(t<T[i]||t>T[i+k+1])
            return 0.0;
        else
        {
            double coffcient1,coffcient2;//凸组合系数1，凸组合系数2
            double denominator=0.0;//分母
            denominator=T[i+k]-T[i];//递推公式第一项分母
            if(denominator==0.0)//约定0/0
                coffcient1=0.0;
            else
                coffcient1=(t-T[i])/denominator;
            denominator=T[i+k+1]-T[i+1];//递推公式第二项分母
            if(0.0==denominator)//约定0/0
                coffcient2=0.0;
            else
                coffcient2=(T[i+k+1]-t)/denominator;
            value1=coffcient1*BasicFunctions(t,i,k-1,T);//递推公式第一项的值
            value2=coffcient2*BasicFunctions(t,i+1,k-1,T);//递推公式第二项的值
            value=value1+value2;//基函数的值
        }
    }
    return value;
}

std::vector<double> CurveUtil::BasisFunctions(double t, int i, int k, std::vector<double> &T)
{
    std::vector<double> basisFunctions(k + 1);
    basisFunctions[0] = 1.0;

    std::vector<double> left(k + 1);
    std::vector<double> right(k + 1);

    for (int j = 1; j <= k; j++)
    {
        left[j] = t - T[i + 1 - j];
        right[j] = T[i + j] - t;

        double saved = 0.0;

        for (int r = 0; r < j; r++)
        {
            double temp = basisFunctions[r] / (right[r + 1] + left[j - r]);
            basisFunctions[r] = saved + right[r + 1] * temp;
            saved = left[j - r] * temp;
        }
        basisFunctions[j] = saved;
    }
    return basisFunctions;
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

std::vector<double> CurveUtil::GetUkByThroughPoints(const std::vector<Point3d> throughPoints)
{
    int n = throughPoints.size() - 1;
    //计算弦长
    double d = 0.0;
    for (int i = 1; i <= n; i++)
    {
        d += throughPoints[i].Distance(throughPoints[i-1]);
    }
    //计算uk
    std::vector<double> uk;
    uk.resize(n+1,0.0);
    uk[n] = 1.0;
    for (int i = 1; i <= n - 1; i++)
    {
        uk[i] = uk[i-1] + (throughPoints[i].Distance(throughPoints[i-1]))/d;
    }
    return uk;

}
std::vector<double> CurveUtil::GetKnotVectorByThroughPoints(int k,int pointsCount,const std::vector<double> _uk)
{
    std::vector<double> knotVector;
    std::vector<double> uk = _uk;

    int size = pointsCount;
    int n = size - 1;
    int m = n + k + 1;

    knotVector.resize(m + 1, 0.0);
    for (int i = m - k; i <= m; i++)
    {
        knotVector[i] = 1.0;
    }

    for (int j = 1; j <= static_cast<int>(n - k + 1); j++)
    {
        double temp = 0.0;
        for (int i = j; i <= static_cast<int>(j + k - 1); i++)
        {
            temp += uk[i];
        }
        knotVector[j + k] = (1.0 / k) * temp;
    }
    return knotVector;
}
