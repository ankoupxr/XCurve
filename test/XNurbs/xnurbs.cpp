
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
    for (int i = 0; i < m_controlPoints.size(); i++)
    {
        for (int j = 0; j < m_controlPoints[i].size(); j++)
        {
            delete[] m_glcontrolPoints[i][j];
        }
        delete[] m_glcontrolPoints[i];
    }
    delete[] m_glcontrolPoints;

    delete[] m_glknots;

}

void xnurbs::draw()
{


}
