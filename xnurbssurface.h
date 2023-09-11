#ifndef XNURBSSURFACE_H
#define XNURBSSURFACE_H

#include <vector>
#include <xcurve.h>
#include <point3dw.h>
#include <curveutil.h>

class XNurbsSurface : xcurve
{
public:
    XNurbsSurface(std::vector<std::vector<Point3dW>> controlPoints,
                  std::vector<std::vector<double>> v,std::vector<std::vector<double>> u,int _m,int _n);
    ~XNurbsSurface();
    double BasicFunction(double t,int i,int k,std::vector<double>& T);
    void GetKnotVector(std::vector<double>& T,int nCount,int num,int k, bool bU);//获取节点矢量
    void GetALLKnotVector();
    void ComputeNurbsSurface();
    void draw();
private:
    int m,p;
    int n,q;
    double m_step = 0.05;
    std::vector<std::vector<Point3dW>> m_controlPoints;
    std::vector<std::vector<double>> m_v;
    std::vector<std::vector<double>> m_u;
    std::vector<double> m_weights;
    std::vector<Point3d> m_uSurFacePoint;
    std::vector<Point3d> m_vSurFacePoint;
};

#endif // XNURBSSURFACE_H
