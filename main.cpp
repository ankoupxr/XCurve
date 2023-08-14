#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include "BezierCurve.h"




int main()
{
    std::vector<XCurve::Point3d> points;
    points.push_back(XCurve::Point3d(0, 0,0));
    points.push_back(XCurve::Point3d(1, 3, 0));
    points.push_back(XCurve::Point3d(2, 1, 0));
    points.push_back(XCurve::Point3d(3, 4, 0));


    double t = 0.5;
    auto result = 
        XCurve::BezierCurve::ComputePointByDeCasteliau(points, 4, t);
    result.PrintCoordinates();
}
