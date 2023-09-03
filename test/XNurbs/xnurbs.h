
#ifndef XNURBS_H
#define XNURBS_H

#include <GL/glut.h>
#include <point3dw.h>
#include <vector>
#include <xcurve.h>
#include <bsplinecurve.h>
#include <mathutil.h>

class xnurbs : xcurve
{
public:
    xnurbs();
    xnurbs(std::vector<std::vector<Point3dW>> controlPoints,std::vector<float> knots);
    ~xnurbs();
    void draw();
    std::vector<Point3dW> ComputeRationalCurveDerivs(int degree, int derivative, const std::vector<double>& knotVector, double paramT, const std::vector<Point3dW>& controlPoints);
private:
    std::vector<std::vector<Point3dW>> m_controlPoints;
    float*** m_glcontrolPoints;
    std::vector<float> m_knots;
    float* m_glknots;
    std::vector<Point3dW> m_curvePoints;
};

#endif // XNURBS_H
