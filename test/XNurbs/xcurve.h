#ifndef XCURVE_H
#define XCURVE_H

#include <point3dw.h>
#include <point3d.h>
#include <GL/glut.h>

class xcurve
{
public:
    xcurve();
    void drawline(Point3dW& start,Point3dW& end);
};

#endif // XCURVE_H
