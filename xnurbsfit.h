
#ifndef XNURBSFIT_H
#define XNURBSFIT_H

#include <curveutil.h>
#include <mathutil.h>
#include <xnurbscurve.h>
#include <xnurbssurface.h>

class XNurbsFit
{
public:
    static xnurbscurve GlobalInterpolationCurve(std::vector<Point3d> points,int n,int k);
    static XNurbsSurface GlobalInterpolationSurf(std::vector<Point3d> points,int n,int m);
};

#endif // XNURBSFIT_H
