#include <math.h>
#include "utilities.h"

StatusDouble compareDouble(double number1, double number2)
{
    const double eps = 1e-6;                    /**< error of double */

    if ( fabs(number1 - number2) < eps ) return EQUALS;
    if (     (number1 - number2) > eps ) return GREATER;

    return LESS;
}
