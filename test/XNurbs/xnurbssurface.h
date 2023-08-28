#ifndef XNURBSSURFACE_H
#define XNURBSSURFACE_H

#include <vector>
#include <point3dw.h>

class XNurbsSurface
{
public:
    XNurbsSurface();
    ~XNurbsSurface();
    void GetKnotVector(std::vector<double> T,int nCount,int num,int order, bool bU);//获取节点矢量
    void BasicFunction(double u,int i,int k,std::vector<double> T);
    void DrawGrid();
private:
    int m,p;
    int n,q;
    std::vector<std::vector<Point3dW>> m_controlPoints;
    std::vector<double> m_v;
    std::vector<double> m_u;
    std::vector<double> m_weights;

};

#endif // XNURBSSURFACE_H
