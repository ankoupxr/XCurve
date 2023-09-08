
#include "xnurbscircle.h"

xnurbscircle::xnurbscircle()
{

}

xnurbscircle::xnurbscircle(Point3d center,Vector3d X, Vector3d Y,double r,double ths,double the)
{
    if(the < ths)
    {
        the = 360 + the;
    }
    theta = the - ths;
    if(theta <= 90)
    {
        narcs = 1;
    }
    else if(theta <= 180)
    {
        narcs = 2;
    }
    else if(theta <= 270)
    {
        narcs = 3;
    }
    else
    {
        narcs = 4;
    }
    double dtheta = theta / narcs;
    int n = 2 * narcs;
    double w1 = cos(dtheta/2.0);
    p0 = center + r * cos(ths);
    t0 = X * (-sin(ths)) + Y * cos(ths);
    Point3dW pw0(p0.GetX(),p0.GetY(),p0.GetZ(),w1);
    m_controlPoints.push_back(pw0);
    int index = 0;
    double angle = ths;
    for (int i = 0; i <= narcs; i++)
    {
        angle = angle + dtheta;

    }
    int j = 2 * narcs + 1;
    m_knots.resize(3+j);
    for(int i = 0;i < 3;i++)
    {
        m_knots[i] = 0.0;
        m_knots[i+j] = 1.0;
    }

    switch(narcs)
    {
    case 1:break;
    case 2: m_knots[3] = m_knots[4] = 0.5;break;
    case 3: m_knots[3] = m_knots[4] = 1.0/3;
            m_knots[5] = m_knots[6] = 2.0/3;
            break;
    case 4: m_knots[3] = m_knots[4] = 0.25;
            m_knots[5] = m_knots[6] = 0.5;
            m_knots[7] = m_knots[8] = 0.75;
            break;
    }

}
