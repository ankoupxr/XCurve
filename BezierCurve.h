#include "Point3d.h"
#include "Curve.h"
#include <vector>

namespace XCurve
{
	class Point3d;
	class BezierCurve : Curve
	{
	public:
		/// <summary>
		/// ͨ��Bernstein����ʽ����Bezier�ĵ�
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




	private:

	};

}