#include "Point3d.h"
#include <iostream>
#include <Eigen/Dense>
#include "Curve.h"

namespace XCurve
{
	enum BSplineCurveType//B��������
	{
		uniform,//����
		quniform//׼����
	};

	class BSplineCurve : Curve
	{
	public:
		BSplineCurve(int _k,int type,std::vector<Point3d> controlPoints) 
		{
			k = _k;
			n = controlPoints.size() - 1;
			m_controlPoints = controlPoints;
			m_type = type;

			double u_tmp = 0.0;
			m_knots.push_back(u_tmp);//�Ȱ�0.0����

			if (type == uniform)//����
			{
				double dis_u = 1.0 / (k + n);
				for (int i = 1; i < n + k + 1; i++) //n + k + 1���ֶ�
				{
					u_tmp += dis_u;
					m_knots.push_back(u_tmp);
				}
			}
			else if (type == quniform)//׼����
			{
				int j = 3;//�ظ���
				double dis_u = 1.0 / (k + n - (j - 1) * 2);
				for (int i = 1; i < j; i++)
				{
					m_knots.push_back(u_tmp);
				}
				for (int i = j; i < n + k - j + 2; i++)
				{
					u_tmp += dis_u;
					m_knots.push_back(u_tmp);
				}
				for (int i = n + k - j + 2; i < n + k + 1; i++)//n + k + 1���ֶ�
				{
					m_knots.push_back(u_tmp);
				}
			}

			uStart = m_knots[k - 1];
			uEnd = m_knots[n + 1];//����u������
		};
		~BSplineCurve() {
			m_controlPoints.clear();
			m_knots.clear();
			m_curvePoints.clear();
		};

		double BSplineBernstein(int i, int k, double u)
		{
			double Ber = 0.0;
			if (k == 1)
			{
				if (m_knots[i] <= u && m_knots[i+1] > u) 
				{
					Ber = 1.0;
				}
				else
				{
					Ber = 0.0;
				}
			}
			else if (k >= 2)
			{
				double A = 0.0;
				double B = 0.0;

				if (m_knots[i+k-1] - m_knots[i] == 0.0)
				{
					A = 0.0;//Լ����ĸΪ0ʱ��������ʽΪ0
				}
				else
				{
					A = (u - m_knots[i]) / (m_knots[i+k-1] - m_knots[i]);
				}

				if (m_knots[i+k] - m_knots[i+1] == 0.0)
				{
					B = 0.0;//Լ����ĸΪ0ʱ��������ʽΪ0
				}
				else
				{
					B = (m_knots[i+k] - u) / (m_knots[i + k] - m_knots[i + 1]);
				}

				Ber = A * BSplineBernstein(i, k - 1, u) + B * BSplineBernstein(i + 1, k - 1, u);//�ݹ�
			}
			return Ber;
		};

		/// <summary>
		/// ����B����
		/// </summary>
		void Draw() 
		{
			int r = 0;
			for (double u = uStart;u <= uEnd;u+=delta_u) 
			{
				Point3d pu;
				for (int i = 0; i < n + 1; i++)
				{
					double xtmp = m_controlPoints[i].Location()(0);
					double ytmp = m_controlPoints[i].Location()(1);
					double BerTmp = BSplineBernstein(i, k, u);
					pu.SetX(pu.GetX() + xtmp * BerTmp);
					pu.SetY(pu.GetY() + ytmp * BerTmp);
					m_curvePoints.push_back(pu);
				}
			}
		}

		void AddKnotPoint()
		{

		};
	private:
		std::vector<Point3d> m_controlPoints;//���Ƶ�
		std::vector<double> m_knots;//�ڵ�����
		std::vector<Point3d> m_curvePoints;//���߹켣��
		double delta_u = 0.01;
		double uStart;
		double uEnd;
		int k;//����
		int n;//���Ƶ���-1
		int m_type; //B��������
	};
}