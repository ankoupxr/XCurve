#include "mathutil.h"

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
