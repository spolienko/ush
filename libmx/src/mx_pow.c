#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
	double temp;

    if (pow <= 0) {
        return 1;
    }
    temp = n;
    for(;pow-1 > 0; --pow) {
        n *= temp;
    }
    return n;
}
