#include "stdafx.h"
#include "algebra.h"


const double MACHINE_EPSILON = 1e-9;


bool
isEqual(double a, double b)
{
	double c = fabs(a);
	double d = fabs(b);

	d = max(c, d);
	return (d == 0.0) ? true : (fabs(a - b) / d) <= MACHINE_EPSILON;
}

bool
isZero(double a)
{
	return a > -MACHINE_EPSILON && a < MACHINE_EPSILON;
}

bool
lessThanZero(double a)
{
	return a < MACHINE_EPSILON;
}