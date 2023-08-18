#include <vector>

namespace XCurve
{
	class Curve
	{
	public:


		static double Bernstein(unsigned int i, unsigned int degree, double paramT) 
		{
			if (i < 0 || i > degree)
			{
				return 0.0;
			}

			if (i == degree)
			{
				return 1.0;
			}

			std::vector<double> temp;
			temp.resize(degree + 1);

			temp[degree - i] = 1.0;
			double t1 = 1.0 - paramT;

			for (unsigned int k = i; k <= degree; k++)
			{
				for (unsigned int j = degree; j >= k; j--)
				{
					temp[j] = t1 * temp[j] + paramT * temp[j - 1];
				}
			}
			return temp[degree];
		};

		static void AllBernstein(unsigned int degree, double paramT, std::vector<double>& bernsteinArray)
		{
			bernsteinArray.resize(degree + 1);

			bernsteinArray[0] = 1.0;
			double t1 = 1.0 - paramT;
			for (unsigned int j = 1; j <= degree; j++)
			{
				double saved = 0.0;
				for (unsigned int k = 0; k < j; k++)
				{
					double temp = bernsteinArray[k];
					bernsteinArray[k] = saved + t1 * temp;
					saved = paramT * temp;
				}
				bernsteinArray[j] = saved;
			}
		};
	};

}