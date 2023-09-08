
#ifndef XNURBSCIRCLE_H
#define XNURBSCIRCLE_H

#include <xnurbscurve.h>
#include <point3d.h>
#include <point3dw.h>
#include <vector3d.h>

class xnurbscircle
{
public:
    xnurbscircle();
    xnurbscircle(Point3d center,Vector3d X, Vector3d Y,double r,double ths,double the);
    void drawCircle();
private:
    double theta;
    int narcs;//圆弧段数
    Point3d p0;
    Vector3d t0;
    std::vector<Point3dW> m_controlPoints;
    std::vector<double> m_knots;
};

#endif // XNURBSCIRCLE_H
