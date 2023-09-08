
#ifndef VECTOR3D_H
#define VECTOR3D_H


#include <math.h>

class Vector3d
{
public:
    Vector3d(double _x=0,double _y = 0,double _z =0)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    Vector3d normalize() const { return((*this) / Norm()); };
    double Norm        () const { return sqrt(NormSquared()); };
    double NormSquared() const {return x*x+y*y+z*z;};

    Vector3d  operator +  (const Vector3d &v) const { return Vector3d(x+v.x, y+v.y, z+v.z); }
    Vector3d& operator += (const Vector3d &v)       { x+=v.x; y+=v.y; z+=v.z; return *this; }
    Vector3d  operator -  () const                 { return Vector3d(-x, -y, -z); }
    Vector3d  operator -  (const Vector3d &v) const { return Vector3d(x-v.x, y-v.y, z-v.z); }
    Vector3d& operator -= (const Vector3d &v)       { x-=v.x; y-=v.y; z-=v.z; return *this; }
    Vector3d  operator *  (double s) const              { return Vector3d(x*s, y*s, z*s); }
    Vector3d& operator *= (double s)                { x*=s; y*=s; z*=s; return *this; }
    Vector3d  operator /  (double s) const          { return (*this)* (1/s); }
    Vector3d& operator /= (double s)                { return (*this)*=(1/s); }

private:
    double x,y,z;
};

#endif // VECTOR3D_H
