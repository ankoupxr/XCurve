#include "xnurbssurface.h"

XNurbsSurface::XNurbsSurface(std::vector<std::vector<Point3dW>> controlPoints,
                             std::vector<double> v,std::vector<double> u,int _m,int _n,
                             std::vector<std::vector<double>> weights)
{

}

void XNurbsSurface::GetKnotVector(std::vector<double> T,int nCount,int num,int order, bool bU)
{

}


double XNurbsSurface::BasicFunction(double u,int i,int k,double T)
{

}


void XNurbsSurface::DrawGrid()
{
    for(size_t i = 0;i < n+1;i++)
    {
        GetKnotVector(m_u,i,m,p,true);
    }
    for(size_t i = 0;i < m+1;i++)
    {
        GetKnotVector(m_v,i,n,q,false);
    }

    double t = 0.1;//步长
    for(double u = 0.0; u <= 1.0;u+=t)
    {
        for(double v = 0.0;v <= 1.0;v+=t)
        {
            Point3dW sp(0,0,0,0);
            for(size_t i = 0;i < n+1;i++)
            {
                for(size_t j = 0;j < m+1;j++)
                {
                    double BasU = BasicFunction(u,j,p,m_u[i]);
                    double BasV = BasicFunction(v,i,q,m_v[j]);
                    sp +=
                }
            }
        }
    }
}
