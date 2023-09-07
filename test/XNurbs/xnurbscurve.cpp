
#include "xnurbscurve.h"

xnurbscurve::xnurbscurve()
{

}

xnurbscurve::xnurbscurve(std::vector<Point3dW> controlPoints,std::vector<double> knots,int k)
{
    this->m_controlPoints = controlPoints;
    this->m_knots = knots;
    this->k = k;
    this->n = controlPoints.size() - 1;
}

xnurbscurve::~xnurbscurve()
{
}

void xnurbscurve::GetKnotVector()
{
    for (int i = 0; i <= k; i++)
    {
        m_knots[i] = 0.0;
    }
    for (int i = n+1; i <= n+k+1; i++)
    {
        m_knots[i] = 1.0;
    }
    for(int i=k+1;i<=n;i++)
    {
        double sum=0.0;
        for(int j=k+1;j<=i;j++)//公式（5-24）
        {
            double numerator=0.0;//计算分子
            for(int loop=j-k;loop<=j-1;loop++)
            {
                numerator+=sqrt((m_controlPoints[loop].GetX()-m_controlPoints[loop-1].GetX())*(m_controlPoints[loop].GetX()-m_controlPoints[loop-1].GetX())
                                  +(m_controlPoints[loop].GetY()-m_controlPoints[loop-1].GetY())*(m_controlPoints[loop].GetY()-m_controlPoints[loop-1].GetY()));//计算两个点之间的距离
            }
            double denominator=0.0;//计算分母
            for(int loop1=k+1;loop1<=n+1;loop1++)
            {
                for(int loop2=loop1-k;loop2<=loop1-1;loop2++)
                {
                    denominator+=sqrt((m_controlPoints[loop2].GetX()-m_controlPoints[loop2-1].GetX())*(m_controlPoints[loop2].GetX()-m_controlPoints[loop2-1].GetX())+
                                        (m_controlPoints[loop2].GetY()-m_controlPoints[loop2-1].GetY())*(m_controlPoints[loop2].GetY()-m_controlPoints[loop2-1].GetY()));//计算两个点之间的距离
                }
            }
            sum+=numerator/denominator;//计算节点值
        }
        m_knots[i]=sum;
    }
}

void xnurbscurve::ComputeRationalCurve()
{
    GetKnotVector();
    m_curvePoints.clear();
    int n = m_controlPoints.size() - 1;
    for(double u = 0;u<=1;u += m_step)
    {
        Point3dW p(0,0,0,1);
        double denominator = 0.0;
        for (int i = 0; i <= n; i++)
        {
            double factor = CurveUtil::BasicFunctions(i, k, m_knots,u) * m_controlPoints[i].GetW();
            denominator += factor;
            p.SetX(p.GetX()+m_controlPoints[i].GetX() * factor);
            p.SetY(p.GetY()+m_controlPoints[i].GetY() * factor);
            p.SetZ(p.GetZ()+m_controlPoints[i].GetZ() * factor);
        }
        p.SetX(p.GetX()/denominator);
        p.SetY(p.GetY()/denominator);
        p.SetZ(p.GetZ()/denominator);
        m_curvePoints.push_back(p);
    }
}


void xnurbscurve::draw()
{
    for(size_t i = 0;i < m_curvePoints.size()-1;i++)
    {
        drawline(m_curvePoints[i],m_curvePoints[i+1]);
    }
}
