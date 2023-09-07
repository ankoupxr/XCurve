#include "xnurbssurface.h"

XNurbsSurface::XNurbsSurface(std::vector<std::vector<Point3dW>> controlPoints,
                             std::vector<std::vector<double>> v,std::vector<std::vector<double>> u,int _m,int _n)
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
    for (int i = 0; i < n + 1; i++)
    {
        GetKnotVector(m_u[i],i,m,p,true);
    }
    for (int i = 0; i < m + 1; i++)
    {
        GetKnotVector(m_v[i],i,n,q,false);
    }

    for (double u = 0.0;u <= 1.0;u += m_step)
    {
        for (double v = 0.0;v <= 1.0;v += m_step)
        {
            Point3dW point(0,0,0,1);
            for (int i = 0;i < n + 1;i++)
            {
                for (int j = 0; j < m + 1; j++)
                {
                    double BasicU = BasicFunction(u,j,p,m_u[i]);
                    double BasicV = BasicFunction(v,i,q,m_v[j]);
                    point.SetX(point.GetX()+m_controlPoints[i][j].GetX()*point.GetW()*BasicU*BasicV);
                    point.SetY(point.GetY()+m_controlPoints[i][j].GetY()*point.GetW()*BasicU*BasicV);
                    point.SetZ(point.GetZ()+m_controlPoints[i][j].GetZ()*point.GetW()*BasicU*BasicV);
                    point.SetW(point.GetW()+m_controlPoints[i][j].GetW()*point.GetW()*BasicU*BasicV);
                }
            }
            point.SetX(point.GetX()/point.GetW());
            point.SetY(point.GetY()/point.GetW());
            point.SetZ(point.GetZ()/point.GetW());
            m_uSurFacePoint.push_back(point);
        }
    }

    for (double v = 0.0;v <= 1.0;v += m_step)
    {
        for (double u = 0.0;u <= 1.0;u += m_step)
        {
            Point3dW point(0,0,0,1);
            for (int i = 0;i < n + 1;i++)
            {
                for (int j = 0; j < m + 1; j++)
                {
                    double BasicU = BasicFunction(u,j,p,m_u[i]);
                    double BasicV = BasicFunction(v,i,q,m_v[j]);
                    point.SetX(point.GetX()+m_controlPoints[i][j].GetX()*point.GetW()*BasicU*BasicV);
                    point.SetY(point.GetY()+m_controlPoints[i][j].GetY()*point.GetW()*BasicU*BasicV);
                    point.SetZ(point.GetZ()+m_controlPoints[i][j].GetZ()*point.GetW()*BasicU*BasicV);
                    point.SetW(point.GetW()+m_controlPoints[i][j].GetW()*point.GetW()*BasicU*BasicV);
                }
            }
            point.SetX(point.GetX()/point.GetW());
            point.SetY(point.GetY()/point.GetW());
            point.SetZ(point.GetZ()/point.GetW());
            m_vSurFacePoint.push_back(point);
        }
    }
}


void XNurbsSurface::GetKnotVector(std::vector<double>& T,int nCount,int num,int k, bool bU)
{
    //小于等于曲线次数k的节点值为0
    for(int i = 0;i <= k;i++)
    {
        T[i] = 0.0;
    }
    //大于n的节点值为1
    for(int i = num+1;i <= num + k + 1;i++)
    {
        T[i] = 1.0;
    }
    //计算其他节点值
    for(int i = k+1;i <= num; i++)
    {
        double sum = 0.0;
        for(int j = k + 1;j <= i;j++)
        {
            double numerator = 0.0;//计算分子
            for (int loop = j - k;loop  <= j-1; loop++)
            {
                if(bU)//选择计算节点矢量U还是计算节点矢量V
                    numerator+=(m_controlPoints[nCount][loop].GetX()-m_controlPoints[nCount][loop-1].GetX())*
                                     (m_controlPoints[nCount][loop].GetX()-m_controlPoints[nCount][loop-1].GetX())
                                 +(m_controlPoints[nCount][loop].GetY()-m_controlPoints[nCount][loop-1].GetY())*
                                       (m_controlPoints[nCount][loop].GetY()-m_controlPoints[nCount][loop-1].GetY());
                else
                    numerator+=(m_controlPoints[loop][nCount].GetX()-m_controlPoints[loop-1][nCount].GetX())*
                                     (m_controlPoints[loop][nCount].GetX()-m_controlPoints[loop-1][nCount].GetX())
                                 +(m_controlPoints[loop][nCount].GetY()-m_controlPoints[loop-1][nCount].GetY())*
                                       (m_controlPoints[loop][nCount].GetY()-m_controlPoints[loop-1][nCount].GetY());
            }
            double denominator = 0.0;//计算分母
            for(int loop1 = k+1;loop1 <= num+1;loop1++)
            {
                for (int loop2 = loop1 - k;loop2 <= loop1 - 1;loop2++)
                {
                    if(bU)
                    {
                        denominator+=(m_controlPoints[nCount][loop2].GetX()-m_controlPoints[nCount][loop2-1].GetX())*
                                           (m_controlPoints[nCount][loop2].GetX()-m_controlPoints[nCount][loop2-1].GetX())
                                       +(m_controlPoints[nCount][loop2].GetY()-m_controlPoints[nCount][loop2-1].GetY())*
                                             (m_controlPoints[nCount][loop2].GetY()-m_controlPoints[nCount][loop2-1].GetY());
                    }
                    else
                    {
                        denominator+=(m_controlPoints[loop2][nCount].GetX()-m_controlPoints[loop2-1][nCount].GetX())*
                                           (m_controlPoints[loop2][nCount].GetX()-m_controlPoints[loop2-1][nCount].GetX())+
                                       (m_controlPoints[loop2][nCount].GetY()-m_controlPoints[loop2-1][nCount].GetY())*
                                           (m_controlPoints[loop2][nCount].GetY()-m_controlPoints[loop2-1][nCount].GetY());
                    }
                }
            }
            sum+=numerator/denominator;
        }
        T[i] = sum;
    }

}

double XNurbsSurface::BasicFunction(double t,int i,int k,std::vector<double>& T)
{
    double value1,value2,value;
    if(k==0)
    {
        if(t>=T[i] && t<T[i+1])
            return 1.0;
        else
            return 0.0;
    }
    if(k>0)
    {
        if(t<T[i]||t>T[i+k+1])
            return 0.0;
        else
        {
            double coffcient1,coffcient2;//凸组合系数1，凸组合系数2
            double denominator=0.0;//分母
            denominator=T[i+k]-T[i];//递推公式第一项分母
            if(denominator==0.0)//约定0/0
                coffcient1=0.0;
            else
                coffcient1=(t-T[i])/denominator;
            denominator=T[i+k+1]-T[i+1];//递推公式第二项分母
            if(0.0==denominator)//约定0/0
                coffcient2=0.0;
            else
                coffcient2=(T[i+k+1]-t)/denominator;
            value1=coffcient1*BasicFunction(t,i,k-1,T);//递推公式第一项的值
            value2=coffcient2*BasicFunction(t,i+1,k-1,T);//递推公式第二项的值
            value=value1+value2;//基函数的值
        }
    }
    return value;
}

void XNurbsSurface::draw()
{
    Point3dW temp,base;
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
