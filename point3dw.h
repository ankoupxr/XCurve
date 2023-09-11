#ifndef Point3dWW_H
#define Point3dWW_H

#include <vector3d.h>
#include <iostream>


class Point3dW
{
public:
    Point3dW()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
    Point3dW(double _x, double _y, double _z,double _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    ~Point3dW()
    {

    }

    void SetX(const double _x)
    {
        x = _x;
    }

    void SetY(const double _y)
    {
        y = _y;
    }

    void SetZ(const double _z)
    {
        z = _z;
    }

    void SetW(const double _w)
    {
       w = _w;
    }


    double GetX()
    {
        return x;
    }

    double GetY()
    {
        return y;
    }

    double GetZ()
    {
        return z;
    }

    double GetW()
    {
        return w;
    }

private:
    //Eigen::Vector4d m_coord;
    double x,y,z,w;
};
#endif // Point3dW_H
