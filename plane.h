
#ifndef PLANE_H
#define PLANE_H

#include <point3d.h>
#include <vector3d.h>


class Plane
{
public:
    Plane();
    Plane(const Point3d& o,const Vector3d& normal);
};

#endif // PLANE_H
