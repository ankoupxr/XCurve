
#include "xnurbscircle.h"

xnurbscircle::xnurbscircle()
{

}

xnurbscircle::xnurbscircle(Point3d center,double r,double ths,double the)
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
}
