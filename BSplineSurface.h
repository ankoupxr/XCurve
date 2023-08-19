#include "Point3d.h"
#include <vector>

namespace XCurve
{
	class BSplineSurface {
		private:
			int m_u_degree;//u方向阶数
			int m_v_degree;//v方向阶数

			double m_u;
			double m_v;

			std::vector<Point3d> m_controlPoints;
			std::vector<double> m_knots;
			std::vector<Point3d> m_surfacePoints;//曲线轨迹点
		public:
			BSplineSurface(int u_degree, int v_degree,
				std::vector<Point3d>& controlPoints, std::vector<double>& knots,double _t)
			{
				this->m_u_degree = u_degree;
				this->m_v_degree = v_degree;
				this->m_controlPoints = controlPoints;
				this->m_knots = knots;
			};

			double BSplineSurfaceBernstein(int i, int degree,double m_t)
			{
				if (degree == 0)
				{
					return (m_t >= m_knots[i] && m_t < m_knots[i + 1]) ? 1.0 : 0.0;
				}
				double denom1 = m_knots[i + degree] - m_knots[i];
				double denom2 = m_knots[i + degree + 1] - m_knots[i + 1];

				double term1 = (denom1 > 0) ? ((m_t - m_knots[i]) / denom1 * BSplineSurfaceBernstein(i, degree - 1,m_t)) : 0.0;
				double term2 = (denom2 > 0) ? ((m_knots[i + degree + 1] - m_t) / denom2 * BSplineSurfaceBernstein(i + 1, degree - 1,m_t)) : 0.0;

				return term1 + term2;
			}

			void Draw()
			{
				int num_u = m_controlPoints.size() - 1;
				int num_v = m_controlPoints.size() - 1;

				std::vector<double> knots_u(num_u + m_u_degree + 2, 0.0);
				std::vector<double> knots_v(num_v + m_v_degree + 2, 0.0);

				for (int i = 0; i < num_u + m_u_degree + 2; i++) {
					if (i < m_u_degree + 1) {
						knots_u[i] = 0.0;
					}
					else if (i <= num_u) {
						knots_u[i] = (i - m_u_degree) / (double)(num_u - m_u_degree + 1);
					}
					else {
						knots_u[i] = 1.0;
					}
				}

				for (int i = 0; i < num_v + m_v_degree + 2; i++) {
					if (i < m_v_degree + 1) {
						knots_v[i] = 0.0;
					}
					else if (i <= num_v) {
						knots_v[i] = (i - m_v_degree) / (double)(num_v - m_v_degree + 1);
					}
					else {
						knots_v[i] = 1.0;
					}
				}

				m_surfacePoints.clear();
				for (int i = 0; i <= num_u; i++) {
					Point3d pu;
					for (int j = 0; j <= num_v; j++) {
						double bu = BSplineSurfaceBernstein(i, m_u_degree,m_u);
						double bv = BSplineSurfaceBernstein(j, m_v_degree,m_v);
						if (j == 0)
						{
							pu.SetX((m_controlPoints[i].GetX()* bu* bv));
						}
						if (j == 1)
						{
							pu.SetY((m_controlPoints[i].GetY() * bu * bv));
						}
						if (j == 2)
						{
							pu.SetZ((m_controlPoints[i].GetZ() * bu * bv));
						}
					}
					m_surfacePoints.push_back(pu);
				}
			}
	};
}