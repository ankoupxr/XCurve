#ifndef XCURVE_H
#define XCURVE_H

#include <point3dw.h>
#include <point3d.h>
#include <GL/glut.h>

class xcurve
{
public:
    xcurve();
    void drawline(Point3d& start,Point3d& end);
    void drawline(Point3dW& start,Point3dW& end);
    void drawPoint(Point3dW& start);
    void drawPoint(Point3d& start);
    void drawline2(Point3d& start,Point3d& end);
};

#endif // XCURVE_H
