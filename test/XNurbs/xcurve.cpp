#include "xcurve.h"

xcurve::xcurve()
{

}

void xcurve::drawline(Point3dW& start,Point3dW& end)
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3f(start.GetX(), start.GetY(), start.GetZ());
    glVertex3f(end.GetZ(), end.GetY(), end.GetZ());
    glEnd();
}
