#include "Point3d.h"
#include "Curve.h"
#include <vector>

namespace XCurve
{
	class BezierCurve : Curve
	{
	public:
		/// <summary>
		/// 通过Bernstein多项式计算Bezier的点
		/// </summary>
		/// <param name="controlPoints"></param>
		/// <param name="degree"></param>
		/// <param name="t"></param>
		/// <returns></returns>
		static Point3d ComputePointByBernstein(const std::vector<Point3d>& controlPoints, unsigned int degree, double t)
		{
			std::vector<double>  bernsteinArray;
			AllBernstein(degree,t,bernsteinArray);

			Point3d temp(0, 0, 0);
			for (unsigned int k = 0; k <= degree; k++)
			{
				controlPoints[k] *= bernsteinArray[k];
				temp += controlPoints[k];
			}
			return temp;
		};

		/// <summary>
		/// 通过DeCasteliau多项式计算Bezier的点
		/// </summary>
		/// <param name="controlPoints"></param>
		/// <param name="degree"></param>
		/// <returns></returns>
		static Point3d ComputePointByDeCasteliau(const std::vector<Point3d> controlPoints, unsigned int degree,double t)
		{
			std::vector<Point3d> tempPoints = controlPoints;

			for (int k = 1; k < degree; k++) {
				for (int i = 0; i < degree - k; i++)
				{
					tempPoints[i].SetX((1 - t) * tempPoints[i].Location()(0) + t * tempPoints[i + 1].Location()(0));
					tempPoints[i].SetY((1 - t) * tempPoints[i].Location()(1) + t * tempPoints[i + 1].Location()(1));
				}
			}

			return tempPoints[0];
		}


	private:

	};

}