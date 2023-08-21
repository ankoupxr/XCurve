#ifndef POINT3D_H
#define POINT3D_H

#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>


class Point3d
{
public:
    Point3d()
    {
        m_coord(0) = 0;
        m_coord(1) = 0;
        m_coord(2) = 0;
    }
    Point3d(float x, float y, float z)
    {
        m_coord(0) = x;
        m_coord(1) = y;
        m_coord(2) = z;
    }

    ~Point3d()
    {

    }

    void SetX(const float x)
    {
        m_coord(0) = x;
    }

    void SetY(const float y)
    {
        m_coord(1) = y;
    }

    void SetZ(const float z)
    {
        m_coord(2) = z;
    }

    float GetX()
    {
        return m_coord(0);
    }

    float GetY()
    {
        return m_coord(1);
    }

    float GetZ()
    {
        return m_coord(2);
    }

    Eigen::Vector3d Location()
    {
        return m_coord;
    }

    Point3d operator*=(const float& v)const
    {
        return Point3d(m_coord(0) * v, m_coord(1) * v, m_coord(2) * v);
    }


    Point3d operator+=(const float& v)const
    {
        return Point3d(m_coord(0) + v, m_coord(1) + v, m_coord(2) + v);
    }

    Point3d operator+=(const Point3d& v)const
    {
        auto location = v.m_coord;
        return Point3d(m_coord(0) + location(0), m_coord(1) + location(1), m_coord(2) + location(2));
    }

    void PrintCoordinates() const
    {
        std::cout << "Coordinates: " << m_coord(0) << ", " << m_coord(1) << ", " << m_coord(2) << std::endl;
    }

private:
    Eigen::Vector3d m_coord;
};
#endif // POINT3D_H
