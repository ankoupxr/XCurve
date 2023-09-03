
#include "xnurbs.h"

xnurbs::xnurbs()
{

}

xnurbs::xnurbs(std::vector<std::vector<Point3dW>> controlPoints,std::vector<float> knots)
{
    this->m_controlPoints = controlPoints;
    this->m_knots = knots;

    this->m_glcontrolPoints = new float**[controlPoints.size()];
    for (int i = 0; i < controlPoints.size(); i++)
    {
        m_glcontrolPoints[i] = new float*[controlPoints[i].size()];
        for (int j = 0;j < m_controlPoints[i].size(); j++)
        {
            m_glcontrolPoints[i][j] = new float[4];
            m_glcontrolPoints[i][j][0] = m_controlPoints[i][j].GetX();
            m_glcontrolPoints[i][j][1] = m_controlPoints[i][j].GetY();
            m_glcontrolPoints[i][j][2] = m_controlPoints[i][j].GetZ();
            m_glcontrolPoints[i][j][3] = m_controlPoints[i][j].GetW();
        }
    }

    this->m_glknots = new float[m_knots.size()];
    for(int i = 0; i < m_knots.size(); i++)
    {
        m_glknots[i] = m_knots.at(i);
    }


}

xnurbs::~xnurbs()
{
}

std::vector<Point3dW> xnurbs::ComputeRationalCurveDerivs(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<Point3dW>& controlPoints)
{
    m_curvePoints.clear();
    std::vector<Point3dW> derivatives(derivative + 1);
    std::vector<Point3dW> ders = BSplineCurve::ComputeDerivatives(degree, derivative, knotVector, paramT, controlPoints);

    std::vector<Point3dW> Aders(derivative + 1);
    for (int i = 0; i < ders.size(); i++)
    {
        Aders[i] = ders[i];
    }
    std::vector<double> wders(derivative + 1);
    for (int i = 0; i < ders.size(); i++)
    {
        wders[i] = ders[i].GetW();
    }

    for (int k = 0; k <= derivative; k++)
    {
        Point3dW v = Aders[k];
        for (int i = 1; i <= k; i++)
        {
            v = v - derivatives[k - i] * MathUtil::Binomial(k, i) * wders[i];
        }
        derivatives[k] = v/wders[0];
        m_curvePoints.push_back(derivatives[k]);
    }
    return derivatives;
}

void xnurbs::draw()
{
    for(size_t i = 0;i < m_curvePoints.size()-1;i++)
    {
        drawline(m_curvePoints[i],m_curvePoints[i+1]);
    }
}
