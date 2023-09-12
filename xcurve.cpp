#include "xcurve.h"

xcurve::xcurve()
{

}

void xcurve::drawline(Point3d start,Point3d end)
{
    glColor3f(255.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3d(start.GetX(), start.GetY(), start.GetZ());
    glVertex3d(end.GetX(), end.GetY(), end.GetZ());
    glEnd();
}


void xcurve::drawline(Point3dW start,Point3dW end)
{
    glColor3f(255.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3d(start.GetX(), start.GetY(), start.GetZ());
    glVertex3d(end.GetX(), end.GetY(), end.GetZ());
    glEnd();
}

void xcurve::drawPoint(Point3d start)
{
    glColor3f(255,255.0,255.0);
    glBegin(GL_POINTS);
    glVertex3d(start.GetX(), start.GetY(), start.GetZ());
    glEnd();
}

void xcurve::drawline2(Point3dW start,Point3dW end)
{
    glColor3f(255.0,255.0,255.0);
    glBegin(GL_LINES);
    //glBegin(GL_POINTS);
    glVertex3f(start.GetX(), start.GetY(), start.GetZ());
    glVertex3f(end.GetX(), end.GetY(), end.GetZ());
    glEnd();
}
