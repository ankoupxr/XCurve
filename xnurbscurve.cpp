
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
        Point3dW p;
        int spanIndex = CurveUtil::FindSpan(k,m_knots,t);
        std::vector<double> BValues = CurveUtil::BasisFunctions(t,spanIndex, k, m_knots);
        for(int i=0;i<=k;i++)
        {
            p.SetX(p.GetX()+m_controlPoints[spanIndex - k + i].GetX()*BValues[i]);
            p.SetY(p.GetY()+m_controlPoints[spanIndex - k + i].GetY()*BValues[i]);
            p.SetZ(p.GetZ()+m_controlPoints[spanIndex - k + i].GetZ()*BValues[i]);
            p.SetW(p.GetW()+m_controlPoints[spanIndex - k + i].GetW() * BValues[i]);
        }
        Point3d res = p.ToPoint3d();
        m_curvePoints.push_back(res);
    }
}


void xnurbscurve::KnotInsert(double u,int s,int r)
{
    int m = n + k +2;//插入前节点个数
    int newc = n + r+1;//插入后的控制点个数
    int index = CurveUtil::FindSpan(k,m_knots,u);
    std::vector<Point3dW> NewControlPoints(newc);
    std::vector<double> NewKnot(NewControlPoints.size() + k +1);
    //设置新节点向量
    for (int i = 0; i <= index; i++)
    {
        NewKnot[i] = m_knots[i];
    }
    for (int i = 0; i <= r; i++)
    {
        NewKnot[index+i] = u;
    }
    for(int i = index+1;i < m;i++)
    {
        NewKnot[i+r] = m_knots[i];
    }
    //设置控制点
    for(int i = 0;i <= index - k;i++)
    {
        NewControlPoints[i] = m_controlPoints[i];
    }
    for (int i = k - s; i < n; i++)
    {
        NewControlPoints[i + r] = m_controlPoints[i];
    }
    //设置新的控制点
    std::vector<Point3dW> NewControlPointsTemp(k - s + 1);
    for (int i = 0; i <= k - s; i++)
    {
        NewControlPointsTemp[i] = m_controlPoints[index - k + i];
    }
    //插入r次
    int L;
    for(int j = 1;j <= r;j++)
    {
        L = index - k + j;
        for (int i = 0; i <= k - j -s; i++)
        {
            double alpha = (u - m_knots[L + i]) / (m_knots[i + k +1]-m_knots[L + i]);
            NewControlPointsTemp[i].SetX(alpha * NewControlPointsTemp[i+1].GetX() * NewControlPointsTemp[i+1].GetW()
                                         + (1 - alpha) * NewControlPointsTemp[i+1].GetX() * NewControlPointsTemp[i+1].GetW());
            NewControlPointsTemp[i].SetY(alpha * NewControlPointsTemp[i+1].GetY() * NewControlPointsTemp[i+1].GetW()
                                         + (1 - alpha) * NewControlPointsTemp[i+1].GetY() * NewControlPointsTemp[i+1].GetW());
            NewControlPointsTemp[i].SetZ(alpha * NewControlPointsTemp[i+1].GetZ() * NewControlPointsTemp[i+1].GetW()
                                         + (1 - alpha) * NewControlPointsTemp[i+1].GetZ() * NewControlPointsTemp[i+1].GetW());
            NewControlPointsTemp[i].SetW(alpha * NewControlPointsTemp[i+1].GetW() + (1-alpha)*NewControlPointsTemp[i+1].GetW());
        }
        NewControlPoints[L] = NewControlPointsTemp[0];
        NewControlPoints[index + r - j -s] = NewControlPointsTemp[k - j - s];
    }

    //载入剩下的控制点和权值
    for (int i = L + 1; i < k - s; i++) {
        NewControlPoints[i] = NewControlPointsTemp[i - L];
    }
    m_controlPoints = NewControlPoints;
    m_knots = NewKnot;
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
        drawPoint(m_controlPoints[i].ToPoint3d());
        if(i+1 <= n)
        {
            drawline2(m_controlPoints[i].ToPoint3d(),m_controlPoints[i+1].ToPoint3d());
        }
    }
}

void xnurbscurve::MakeRevolvedSurf(Point3d S,Vector3d T,double theta)
{
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
        scPoints[i-1].resize(n);
    }
    for(int j=0;j <= n;j++)
    {
        Point3d P = Point3d(m_controlPoints[j].GetX(),m_controlPoints[j].GetY(),m_controlPoints[j].GetZ());
        Point3d O = MathUtil::PointToLine(S,T,P);
        Vector3d X = P - O;
        double r = X.Norm();
        Vector3d Y = T.cross(X);
        Point3d P0 = m_controlPoints[j].ToPoint3d();
        scPoints[0][j] = m_controlPoints[j];
        Vector3d T0 = Y;
        int index = 0;
        angle = 0.0;
        for(int i = 1;i <= narcs;i++)
        {
            Point3d P2 = O + X * r * coses[i] + Y * r * sines[i];
            scPoints[index+2][j] = Point3dW(P2.GetX(),P2.GetY(),P2.GetZ(),m_controlPoints[j].GetW());
            Vector3d T2 = X * (- sines[i])  + Y * coses[i];
            Point3d ins = MathUtil::Intersect3DLines(P0,T0,P2,T2);
            scPoints[index+1][j] = Point3dW(ins.GetX(),ins.GetY(),ins.GetZ(),wm*m_controlPoints[j].GetW());
            index = index + 2;
            if(i < narcs)
            {
                P0 = P2;
                T0 = T2;
            }
        }
    }
    XNurbsSurface surface();
}
