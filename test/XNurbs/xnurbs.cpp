
#include "xnurbs.h"

xnurbs::xnurbs()
{

}

xnurbs::xnurbs(std::vector<Point3dW> controlPoints,std::vector<double> knots,int degree)
{
    this->m_controlPoints = controlPoints;
    this->m_knots = knots;
    this->m_degree = degree;
}

xnurbs::~xnurbs()
{
}

void xnurbs::ComputeRationalCurve()
{
    m_curvePoints.clear();
    int n = m_controlPoints.size() - 1;
    for(double u = 0;u<=1;u += m_step)
    {
        Point3dW p(0,0,0,1);
        double denominator = 0.0;
        for (int i = 0; i <= n; i++)
        {
            double factor = CurveUtil::BasicFunctions(i, m_degree, m_knots,u) * m_controlPoints[i].GetW();
            denominator += factor;
            p.SetX(p.GetX()+m_controlPoints[i].GetX() * factor);
            p.SetY(p.GetY()+m_controlPoints[i].GetY() * factor);
            p.SetZ(p.GetZ()+m_controlPoints[i].GetZ() * factor);
        }
        p /= denominator;
        m_curvePoints.push_back(p);
    }
}


void xnurbs::draw()
{
    for(size_t i = 0;i < m_curvePoints.size()-1;i++)
    {
        drawline(m_curvePoints[i],m_curvePoints[i+1]);
    }
}
