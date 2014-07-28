#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include <iostream>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern const double MACHINE_EPSILON;

bool isEqual(double a, double b);
bool isLessThan(double a, double b);
bool isZero(double a);

bool lessThanZero(double a);


inline double
min(double a, double b)
{
	double c = (a < b) ? a : b;
	if (c != c) {
		// Handle case min(x, NaN)
		return a;
	}
	return c;
}


inline double
max(double a, double b)
{

	double c = (a > b) ? a : b;
	if (c != c) {
		// Handle case max(x, NaN)
		return a;
	}
	return c;
}

inline double Radians(float deg) {
	return ((double)M_PI / 180.0) * deg;
}


inline double Degrees(float rad) {
	return (180.0 / (double)M_PI) * rad;
}

#endif