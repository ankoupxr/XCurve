
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
    m_curvePoints.clear();
    for(double t=0.0;t<=1.0;t+=m_step)
    {
        Point3d p(0,0,0);
        double denominator = 0.0;
        for(int i=0;i<=n;i++)
        {
            double BValue = CurveUtil::BasicFunctions(t,i, k, m_knots);
            p.SetX(p.GetX()+m_controlPoints[i].GetX()*m_controlPoints[i].GetW()*BValue);
            p.SetY(p.GetY()+m_controlPoints[i].GetY()*m_controlPoints[i].GetW()*BValue);
            p.SetZ(p.GetZ()+m_controlPoints[i].GetZ()*m_controlPoints[i].GetW()*BValue);
            denominator += BValue * m_controlPoints[i].GetW();
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

void xnurbscurve::drawControl()
{
    for(int i=0;i<=n;i++)
    {
        drawPoint(m_controlPoints[i]);
        if(i+1 <= n)
        {
        drawline(m_controlPoints[i],m_controlPoints[i+1]);
        }
    }
}

void xnurbscurve::MakeRevolvedSurf(Point3d S,Vector3d T,double theta)
{/*
    int narcs;
    std::vector<double> U(9);
    std::vector<std::vector<Point3dW>> scPoints;
    if(theta <= 90)
    {
        narcs = 1;
    }
    else if(theta <= 270.0)
    {
        narcs = 3;
        U[3] = U[4] = 1.0/3.0;
        U[5] = U[6] = 2.0/3.0;
    }
    else
    {
        narcs = 4;
        U[3] = U[4] = 0.25;
        U[5] = U[6] = 0.5;
        U[7] = U[8] = 0.75;
    }
    double dtheta = (theta/narcs) * 3.1415926 / 180;
    int j = 3 + 2 * (narcs - 1);
    for (int i = 0; i < 3; i++)
    {
        U[i] = 0.0;
        U[j] = 1.0;
    }
    n = 2 * narcs;
    double wm = cos(dtheta/2.0);
    double angle = 0.0;
    std::vector<double> coses(narcs);
    std::vector<double> sines(narcs);
    scPoints.resize(narcs);
    for(int i = 1;i <= narcs;i++)
    {
        angle = angle + dtheta;
        coses[i] = cos(angle);
        sines[i] = sin(angle);
        scPoints[i-1].resize(m);
    }
    for(int j=0;j <= m;j++)
    {
        Point3d O = MathUtil::PointToLine(S,T,m_controlPoints[j]);
        Vector3d X = m_controlPoints[j] - O;
        double r = X.Norm();
        Vector3d Y = T.cross(X);
        Point3dW P0 = m_controlPoints[j];
        scPoints[0][j] = m_controlPoints[j];
        Vector3d T0 = Y;
        int index = 0;
        angle = 0.0;
        for(int i = 1;i <= narcs;i++)
        {
            Point3dW P2 = O + r * coses[i] * X + r * sines[i] * Y;
            P2.SetW(m_controlPoints[j].GetW());
            scPoints[index+2][j] = P2;
            Vector3d T2 = - sines[i] * X + coses[i] * Y;
            Point3d ins = MathUtil::Intersect3DLines(P0,T0,P2,T2);
            scPoints[index+1][j] = Point3dW(ins.GetX(),ins.GetY(),ins.GetZ(),wm*m_controlPoints[j].GetW());
            index = index + 2;
            if(i < narcs)
            {
                P0 = P2;
                T0 = T2;
            }
        }
    }*/
}
