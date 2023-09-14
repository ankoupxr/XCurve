
#ifndef XNURBSCURVE_H
#define XNURBSCURVE_H

#include <GL/glut.h>
#include <point3dw.h>
#include <vector>
#include <xcurve.h>
#include <bsplinecurve.h>
#include <xnurbssurface.h>
#include <mathutil.h>
#include <list>

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
    void KnotInsert(double u,int s,int r);//插入节点
    void KnotRefine(std::vector<double> X,int r);//节点细化
    void DccomposeCurveToBezier();//分解为Bezier曲线
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
