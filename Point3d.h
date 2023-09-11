#ifndef Point3d_H
#define Point3d_H

#include <iostream>
#include <vector3d.h>>

class Point3d
{
public:
    Point3d()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Point3d(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    ~Point3d()
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

    Point3d  operator +  (const Point3d &v) const { return Point3d(x+v.x, y+v.y, z+v.z); }
    Point3d  operator +  (const double &v) const { return Point3d(x+v, y+v, z+v); }
    Point3d& operator += (const Point3d &v)       { x+=v.x; y+=v.y; z+=v.z; return *this; }
    Point3d  operator -  () const                 { return Point3d(-x, -y, -z); }
    Point3d  operator -  (const Point3d &v) const { return Point3d(x-v.x, y-v.y, z-v.z); }
    Point3d& operator -= (const Point3d &v)       { x-=v.x; y-=v.y; z-=v.z; return *this; }
    Point3d  operator *  (double s) const              { return Point3d(x*s, y*s, z*s); }
    Point3d& operator *= (double s)                { x*=s; y*=s; z*=s; return *this; }
    Point3d  operator /  (double s) const          { return (*this)* (1/s); }
    Point3d& operator /= (double s)                { return (*this)*=(1/s); }
    Point3d operator + (const Vector3d &v) {return Point3d(x+v.X(), y+v.Y(), v.Z()+z);}
    //Vector3d operator -  (const Point3d &v) const { return Vector3d(x-v.X(), y-v.Y(), z-v.Z()); }

private:
    //Eigen::Vector4d m_coord;
    double x,y,z;
};
#endif // Point3d_H
