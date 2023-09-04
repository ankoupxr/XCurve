
#include "xnurbs.h"

xnurbs::xnurbs()
{

}

xnurbs::xnurbs(std::vector<Point3dW> controlPoints,std::vector<double> knots,int degree,double paramT)
{
    this->m_controlPoints = controlPoints;
    this->m_knots = knots;
    this->m_degree = degree;
    this->m_paramT = paramT;
}

xnurbs::~xnurbs()
{
}

void xnurbs::ComputeRationalCurve()
{
    m_curvePoints.clear();
    int n = m_controlPoints.size() - 1;
    for(double st = 0.0;st <= 1.0;st += m_step)
    {
        Point3dW p(0,0,0,0);
        int spanIndex = CurveUtil::FindSpan(m_degree,m_knots,st);
        std::vector<double> BasicValue = CurveUtil::BasicFunctions(spanIndex,m_degree,m_knots,st);
        for (unsigned int j = 0; j <= m_degree; j++)
        {
            auto testp = m_controlPoints[spanIndex - m_degree + j];
            auto tb = BasicValue[j];
            p += m_controlPoints[spanIndex - m_degree + j] * BasicValue[j];
            auto d = p;
        }
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
