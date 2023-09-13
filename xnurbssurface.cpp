#include "xnurbssurface.h"

XNurbsSurface::XNurbsSurface(std::vector<std::vector<Point3dW>> controlPoints,
                             std::vector<double> v,std::vector<double> u,int _m,int _n)
{
    this->m_controlPoints = controlPoints;
    this->m_v = v;
    this->m_u = u;
    this->m = _m;
    this->n = _n;
    this->p = _m -1;
    this->q = _n -1;
}

XNurbsSurface::~XNurbsSurface()
{

}


void XNurbsSurface::ComputeNurbsSurface()
{

    for (double u = 0.0;u <= 1.0;u += m_step)
    {
        int uSpanIndex = CurveUtil::FindSpan(p,m_u,u);
        std::vector<double> BasisU = CurveUtil::BasisFunctions(u,uSpanIndex,p,m_u);
        for (double v = 0.0;v <= 1.0;v += m_step)
        {
            int vSpanIndex = CurveUtil::FindSpan(q,m_v,v);
            std::vector<double> BasisV = CurveUtil::BasisFunctions(v,vSpanIndex,q,m_v);
            Point3dW point;
            for (int i = 0;i <= q;i++)
            {
                Point3dW temp;
                for (int j = 0; j <= p; j++)
                {
                    temp.SetX(temp.GetX()+m_controlPoints[uSpanIndex-p+j][vSpanIndex-q+i].GetX()*BasisU[j]);
                    temp.SetY(temp.GetY()+m_controlPoints[uSpanIndex-p+j][vSpanIndex-q+i].GetY()*BasisU[j]);
                    temp.SetZ(temp.GetZ()+m_controlPoints[uSpanIndex-p+j][vSpanIndex-q+i].GetZ()*BasisU[j]);
                    temp.SetW(temp.GetW()+m_controlPoints[uSpanIndex-p+j][vSpanIndex-q+i].GetW()*BasisU[j]);
                }
                point.SetX(point.GetX()+temp.GetX()*BasisV[i]);
                point.SetY(point.GetY()+temp.GetY()*BasisV[i]);
                point.SetZ(point.GetZ()+temp.GetZ()*BasisV[i]);
                point.SetW(point.GetW()+temp.GetW()*BasisV[i]);
            }
            Point3d res = point.ToPoint3d();
            m_uSurFacePoint.push_back(res);
        }
    }

    for (double v = 0.0;v <= 1.0;v += m_step)
    {
        int vSpanIndex = CurveUtil::FindSpan(q,m_v,v);
        std::vector<double> BasisV = CurveUtil::BasisFunctions(v,vSpanIndex,q,m_v);
        for (double u = 0.0;u <= 1.0;u += m_step)
        {
            int uSpanIndex = CurveUtil::FindSpan(p,m_u,u);
            std::vector<double> BasisU = CurveUtil::BasisFunctions(u,uSpanIndex,p,m_u);
            Point3dW point;
            for (int i = 0;i <= q;i++)
            {
                Point3dW temp;
                for (int j = 0; j <= p; j++)
                {
                    temp.SetX(temp.GetX()+m_controlPoints[uSpanIndex-q+j][vSpanIndex-p+i].GetX()*BasisU[j]);
                    temp.SetY(temp.GetY()+m_controlPoints[uSpanIndex-q+j][vSpanIndex-p+i].GetY()*BasisU[j]);
                    temp.SetZ(temp.GetZ()+m_controlPoints[uSpanIndex-q+j][vSpanIndex-p+i].GetZ()*BasisU[j]);
                    temp.SetW(temp.GetW()+m_controlPoints[uSpanIndex-q+j][vSpanIndex-p+i].GetW()*BasisU[j]);
                }
                point.SetX(point.GetX()+temp.GetX()*BasisV[i]);
                point.SetY(point.GetY()+temp.GetY()*BasisV[i]);
                point.SetZ(point.GetZ()+temp.GetZ()*BasisV[i]);
                point.SetW(point.GetW()+temp.GetW()*BasisV[i]);
            }
            Point3d res = point.ToPoint3d();
            m_vSurFacePoint.push_back(res);
        }
    }
}




void XNurbsSurface::draw()
{
    Point3d temp,base;
    int i = 0;
    for (double v = 0.0;v <= 1.0;v += m_step)
    {
        for (double u = 0.0;u <= 1.0;u += m_step)
        {
            temp = m_uSurFacePoint[i];
            if(u != 0)
            {
                drawline(base,temp);
            }
            base = temp;
            i++;
        }
    }
    int j = 0;
    for (double u = 0.0;u <= 1.0;u += m_step)
    {
        for (double v = 0.0;v <= 1.0;v += m_step)
        {
            temp = m_vSurFacePoint[j];
            if(v != 0)
            {
                drawline(base,temp);
            }
            base = temp;
            j++;
        }
    }
}
