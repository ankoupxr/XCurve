
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
    xnurbscurve(std::vector<Point3dW> controlPoints,std::vector<double> knots,int degree);
    ~xnurbscurve();
    void draw();
    std::vector<Point3dW> ComputeRationalCurveDerivs(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<Point3dW>& controlPoints);
    void SetDegree(int degree){
        m_degree = degree;
    };
    void SetParamT(double paramT){
        m_paramT = paramT;
    };
    void ComputeRationalCurve();
private:
    std::vector<Point3dW> m_controlPoints;
    std::vector<double> m_knots;
    int m_degree;
    double m_paramT;
    double m_step=0.01;
    std::vector<Point3dW> m_curvePoints;
};

#endif // XNURBSCURVE_H
