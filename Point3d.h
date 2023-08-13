#include <Eigen/Dense>
#include <Eigen/Core>

namespace XCurve
{
	class Point3d
	{
	public:
		Point3d()
		{
			m_coord(0) = 0;
			m_coord(1) = 0;
			m_coord(2) = 0;
		}
		Point3d(double x,double y, double z)
		{
			m_coord(0) = x;
			m_coord(1) = y;
			m_coord(2) = z;
		}

		~Point3d()
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

		Eigen::Vector3d Location()
		{
			return m_coord;
		}

		Point3d operator*=(const double& v)const
		{
			return Point3d(m_coord(0) * v, m_coord(1) * v, m_coord(2) * v);
		}


		Point3d operator+=(const double& v)const
		{
			return Point3d(m_coord(0) + v, m_coord(1) + v, m_coord(2) + v);
		}

		Point3d operator+=(const Point3d& v)const
		{
			auto location = v.m_coord;
			return Point3d(m_coord(0) + location(0), m_coord(1) + location(1), m_coord(2) + location(2));
		}

	private:
		Eigen::Vector3d m_coord;
	};
}