#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main (void) {
    
    const double EPS = 1e-5;

    double length, temperature, coeff;
    while (scanf ("%lf%lf%lf", &length, &temperature, &coeff) != EOF) {
        if (length < 0 && temperature < 0 && coeff < 0) {
            return 0;
        }

        double formula = (1 + temperature * coeff) * length;

        double low = 0;
        double high = length / 2;
        double half;
        while (high - low > EPS) {
            half = (high + low) / 2;
            double m = ((half * half * 4) + (length * length)) / (8 * half);

            double check = 2 * m * asin (length / (2 * m));
            if (check < formula) {
                low = half;
            } else {
                high = half;
            }
        }

        printf ("%.3f\n", half);
    }

    return 0;
}



