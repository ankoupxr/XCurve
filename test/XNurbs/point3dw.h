#ifndef Point3dWW_H
#define Point3dWW_H

#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>


class Point3dW
{
public:
    Point3dW()
    {
        m_coord(0) = 0;
        m_coord(1) = 0;
        m_coord(2) = 0;
        m_coord(3) = 0;
    }
    Point3dW(double x, double y, double z,double w)
    {
        m_coord(0) = x;
        m_coord(1) = y;
        m_coord(2) = z;
        m_coord(3) = w;
    }

    ~Point3dW()
    {

    }

    void SetX(const double x)
    {
        m_coord(0) = x;
    }

    void SetY(const double y)
    {
        m_coord(1) = y;
    }

    void SetZ(const double z)
    {
        m_coord(2) = z;
    }

    double GetX()
    {
        return m_coord(0);
    }

    double GetY()
    {
        return m_coord(1);
    }

    double GetZ()
    {
        return m_coord(2);
    }

    double GetW()
    {
        return m_coord(3);
    }

    Eigen::Vector4d Location()
    {
        return m_coord;
    }

    Point3dW operator*=(const double& v)const
    {
        return Point3dW(m_coord(0) * v, m_coord(1) * v, m_coord(2) * v, m_coord(3));
    }


    Point3dW operator+=(const double& v)
    {
        return Point3dW(m_coord(0) + v, m_coord(1) + v, m_coord(2) + v, m_coord(3));
    }

    Point3dW operator+=(const Point3dW& v)
    {
        auto location = v.m_coord;
        m_coord(0) = m_coord(0) + location(0);
        m_coord(1) = m_coord(1) + location(1);
        m_coord(2) = m_coord(2) + location(2);
        return Point3dW(m_coord(0), m_coord(1), m_coord(2) , m_coord(3));;
    }

    Point3dW operator-(const Point3dW& v)const
    {
        auto location = v.m_coord;
        return Point3dW(m_coord(0) - v.m_coord.x(), m_coord(1) - v.m_coord.y(), m_coord(2)  - v.m_coord.z(), m_coord(3));
    }

     Point3dW operator*(const double& v)
    {
        m_coord(0) = m_coord(0) * v;
        m_coord(1) = m_coord(1) * v;
        m_coord(2) = m_coord(2) * v;
        return Point3dW(m_coord(0), m_coord(1), m_coord(2) , m_coord(3));;
    }

    Point3dW operator/(const double& v)
    {
        return Point3dW(m_coord(0) / v, m_coord(1) / v, m_coord(2) / v, m_coord(3));
    }

    void PrintCoordinates()
    {
        std::cout << "Coordinates: " << m_coord(0) << ", " << m_coord(1) << ", " << m_coord(2) << std::endl;
    }

private:
    Eigen::Vector4d m_coord;
};
#endif // Point3dW_H
