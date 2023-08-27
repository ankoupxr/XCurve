
#ifndef XNURBS_H
#define XNURBS_H

#include <GL/glut.h>
#include <point3dw.h>
#include <vector>
#include <xcurve.h>

class xnurbs : xcurve
{
public:
    xnurbs();
    xnurbs(std::vector<std::vector<Point3dW>> controlPoints,std::vector<float> knots);
    ~xnurbs();
    void draw();
private:
    std::vector<std::vector<Point3dW>> m_controlPoints;
    float*** m_glcontrolPoints;
    std::vector<float> m_knots;
    float* m_glknots;
};

#endif // XNURBS_H
