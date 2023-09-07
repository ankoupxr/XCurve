
#ifndef XNURBSCIRCLE_H
#define XNURBSCIRCLE_H

#include <xnurbscurve.h>
#include <point3d.h>
#include <point3dw.h>

class xnurbscircle
{
public:
    xnurbscircle();
    xnurbscircle(Point3d center,double r,double ths,double the);
    void drawCircle();
private:
    double theta;
    int narcs;//圆弧段数
    Point3d p0;
    std::vector<Point3dW> m_controlPoints;
};

#endif // XNURBSCIRCLE_H
