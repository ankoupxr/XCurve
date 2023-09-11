#ifndef Point3dWW_H
#define Point3dWW_H

#include <point3d.h>
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


    double GetX() const
    {
        return x;
    }

    double GetY() const
    {
        return y;
    }

    double GetZ() const
    {
        return z;
    }

    double GetW() const
    {
        return w;
    }

    Point3d ToPoint3d(){
        return Point3d(x,y,z);
    }

    Point3dW  operator +  (const Point3dW &v) const { return Point3dW(x+v.x, y+v.y, z+v.z,w); }
    Point3dW  operator +  (const double &v) const { return Point3dW(x+v, y+v, z+v,w); }
    Point3dW& operator += (const Point3dW &v)       { x+=v.x; y+=v.y; z+=v.z; return *this; }
    Point3dW  operator -  () const                 { return Point3dW(-x, -y, -z,w); }
    Point3dW  operator -  (const Point3dW &v) const { return Point3dW(x-v.x, y-v.y, z-v.z,w); }
    Point3dW& operator -= (const Point3dW &v)       { x-=v.x; y-=v.y; z-=v.z; return *this; }
    Point3dW  operator *  (double s) const              { return Point3dW(x*s, y*s, z*s,w); }
    Point3dW& operator *= (double s)                { x*=s; y*=s; z*=s; return *this; }
    Point3dW  operator /  (double s) const          { return (*this)* (1/s); }
    Point3dW& operator /= (double s)                { return (*this)*=(1/s); }
    Point3dW operator + (const Vector3d &v) {return Point3dW(x+v.X(), y+v.Y(), v.Z()+z,w);}
    Vector3d operator -  (const Point3dW &v) { return Vector3d(x-v.GetX(), y-v.GetY(), z-v.GetZ()); }

private:
    //Eigen::Vector4d m_coord;
    double x,y,z,w;
};
#endif // Point3dW_H
