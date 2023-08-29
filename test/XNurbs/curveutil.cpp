#include "curveutil.h"

int CurveUtil::FindSpan(int degree,std::vector<double>& knotVector, double u)
{
    int n = knotVector.size() - degree - 2;

    int low = degree;
    int high = n + 1;
    int mid = static_cast<int>(floor((low+high)/2.0));

    while(u < knotVector[mid] || u >= knotVector[mid+1])
    {
        if(u < knotVector[mid])
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
        mid = (low + high) / 2;
    }
    return(mid);
}
