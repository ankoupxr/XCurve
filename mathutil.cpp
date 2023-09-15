#include "mathutil.h"


bool MathUtil::LUDecomposition(std::vector<std::vector<double>> CompositionMat,
                     std::vector<std::vector<double>>& UpperMat,std::vector<std::vector<double>>& LowMat)
{
    int size = CompositionMat.size();
    LowMat.resize(size);
    UpperMat.resize(size);
    for (int i = 0; i < size; i++)
    {
        LowMat[i].resize(size);
        UpperMat[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            UpperMat[i][j] = 0;
            if (i == j)
            {
                LowMat[i][j] = 1.0;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        double sum = 0;
        for (int j = i; j < size; j++)
        {
            for (int k = 0; k <= i - 1; k++)
            {
                sum += LowMat[i][k] * UpperMat[k][j];
            }
            double temp = CompositionMat[i][j] - sum;
            if (IsAlmostEqualTo(temp, 0.0))
            {
                if (i == j) return false;
                UpperMat[i][j] = 0.0;
            }
            else
            {
                UpperMat[i][j] = temp;
            }
            sum = 0.0;
        }

        for (int x = i + 1; x < size; x++)
        {
            for (int k = 0; k <= i - 1; k++)
            {
                sum += LowMat[x][k] * UpperMat[k][i];
            }
            double temp = CompositionMat[x][i] - sum;
            if (IsAlmostEqualTo(temp, 0.0))
            {
                LowMat[x][i] = 0.0;
            }
            else
            {
                LowMat[x][i] = temp / UpperMat[i][i];
            }
            sum = 0.0;
        }
    }
    return true;
}

bool MathUtil::ForwardBackward(std::vector<std::vector<double>> CompositionMat,std::vector<std::vector<double>>& UpperMat,
                     std::vector<std::vector<double>>& LowMat,std::vector<double>& rhs,std::vector<double>& sol)
{
    int rhssize = rhs.size();
    std::vector<double> column;
    column.resize(rhssize,0.0);
    column[0] = rhs[0] / LowMat[0][0];
    for (int i = 1; i < rhssize; i++)
    {
        double temp = 0.0;
        for (int j = 0; j < i; j++)
        {
            temp += LowMat[i][j] * column[j];
        }
        column[i] = (rhs[i] - temp) / LowMat[i][i];
    }

    int solsize = column.size();
    int n = solsize - 1;
    sol.resize(solsize,0.0);
    sol[n] = column[n] / UpperMat[n][n];
    for (int i = solsize - 2;i >= 0;i--)
    {
        double temp = 0.0;
        for (int j = i; j < solsize; j++)
        {
            temp += UpperMat[i][j] * sol[j];
        }
        sol[i] = (column[i] - temp) / UpperMat[i][i];
    }
    return true;
}

int MathUtil::Factorial(unsigned int number)
{
    if (number == 0)
        return 1;
    else
        return number * Factorial(number - 1);
}

double MathUtil::Binomial(unsigned int number, unsigned int i)
{
    return Factorial(number) / (Factorial(i) * Factorial(number - 1));
}

Point3d MathUtil::PointToLine(Point3d S,Vector3d T,Point3d P)
{
    Vector3d V = P - S;
    Vector3d N = T / T.Norm();
    double D = V.dot(N);
    Point3d Q = S + N * D;
    return Q;
}

Point3d MathUtil::Intersect3DLines(Point3d P0,Vector3d T0,Point3d P2,Vector3d T2)
{
    Vector3d P0P2 = P2 - P0;
    Vector3d crossT0T2 = T0.cross(T2);
    Vector3d crossP0T2 = P0P2.cross(T2);

    double denominator = crossT0T2.dot(crossT0T2);

    if (denominator < 1e-6) {
        // 两条直线平行或重合，无交点
        return Point3d(NAN, NAN, NAN);
    }

    double t = crossP0T2.dot(crossT0T2) / denominator;
    Point3d intersection = P0 + T0 * t;

    return intersection;
}

bool MathUtil::IsAlmostEqualTo(double value1, double value2, double tolerance)
{
    if (IsNaN(value1) || IsNaN(value2))
        return false;
    double eps = (abs(value1) + abs(value2) + 10) * tolerance;
    double delta = value1 - value2;
    return (-eps < delta) && (eps > delta);
}

bool MathUtil::IsNaN(double value)
{
    return value != value;
}

