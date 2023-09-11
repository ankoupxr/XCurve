
#include "xnurbscircle.h"

xnurbscircle::xnurbscircle()
{

}

xnurbscircle::xnurbscircle(Point3d center,Vector3d X, Vector3d Y, double r, double ths, double the)
{
    k = 2;
    if (the < ths)
    {
        the = 360 + the;
    }
    double theta = the - ths;
    int narcs;

    double dtheta = (the-ths) * 3.1415926 / 180;
    Point3dW p0(center.GetX() + r,center.GetY(),0,1);
    Point3dW p1(center.GetX() + r,center.GetY() + r,0,cos(dtheta / 8));
    Point3dW p2(center.GetX(),center.GetY() + r,0,1);
    Point3dW p3(center.GetX() - r ,center.GetY() + r,0,cos(dtheta / 8));
    Point3dW p4(center.GetX() - r,center.GetY(),0,1);
    Point3dW p5(center.GetX() - r,center.GetY() - r,0,cos(dtheta / 8));
    Point3dW p6(center.GetX() ,center.GetY()-r,0,1);
    Point3dW p7(center.GetX() + r,center.GetY() - r,0,cos(dtheta / 8));
    Point3dW p8(center.GetX() + r,center.GetY(),0,1);

    if (theta <= 90)
    {
        narcs = 1;
    }
    else if (theta <= 180)
    {
        narcs = 2;
    }
    else if (theta <= 270)
    {
        narcs = 3;
    }
    else
    {
        narcs = 4;
    }

    m_controlPoints.push_back(p0);
    m_controlPoints.push_back(p1);
    m_controlPoints.push_back(p2);
    m_controlPoints.push_back(p3);
    m_controlPoints.push_back(p4);
    m_controlPoints.push_back(p5);
    m_controlPoints.push_back(p6);
    m_controlPoints.push_back(p7);
    m_controlPoints.push_back(p8);

    n = 8;

    int j = 2 * narcs + 1;
    m_knots.resize(3 + j);
    for (int i = 0; i < 3; i++)
    {
        m_knots[i] = 0.0;
        m_knots[j + 2 - i] = 1.0;
    }
    switch (narcs)
  {
    case 1:
        break;
    case 2:
        m_knots[3] = m_knots[4] = 0.5;
        break;
    case 3:
        m_knots[3] = m_knots[4] = 1.0 / 3;
        m_knots[5] = m_knots[6] = 2.0 / 3;
        break;
    case 4:
        m_knots[3] = m_knots[4] = 0.25;
        m_knots[5] = m_knots[6] = 0.5;
        m_knots[7] = m_knots[8] = 0.75;
        break;
    }
}

void xnurbscircle::drawCircle(){
    ComputeRationalCurve();
    draw();
}
