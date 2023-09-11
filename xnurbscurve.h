
#ifndef XNURBSCURVE_H
#define XNURBSCURVE_H

#include <GL/glut.h>
#include <point3dw.h>
#include <vector>
#include <xcurve.h>
#include <bsplinecurve.h>
#include <mathutil.h>

class xnurbscurve : xcurve
{
public:
    xnurbscurve();
    xnurbscurve(std::vector<Point3dW> controlPoints,std::vector<double> knots,int k);
    ~xnurbscurve();
    void draw();
    void drawControl();
    std::vector<Point3dW> ComputeRationalCurveDerivs(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<Point3dW>& controlPoints);
    void GetKnotVector();//获取节点矢量
    void KnotInsert();
    void ComputeRationalCurve();
    void MakeRevolvedSurf(Point3d S,Vector3d T,double theta);
protected:
    std::vector<Point3dW> m_controlPoints;
    std::vector<double> m_knots;
    int k;
    int n;
    double m_step=0.01;
    std::vector<Point3d> m_curvePoints;
};

#endif // XNURBSCURVE_H
