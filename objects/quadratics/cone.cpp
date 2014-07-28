#include "stdafx.h"
#include "cone.h"

Cone::Cone(Vertex c, double r, double h)
{
	center = c;
	radius = r;
	height = h;
}

bool Cone::intersect(Ray &ray, Hit *hit)
{
	double xd = ray.D.x;
	double yd = ray.D.y;
	double zd = ray.D.z;
	double xo = ray.P.x;
	double yo = ray.P.y;
	double zo = ray.P.z;

	Vector diff(xo - center.x, yo - center.y + height, zo - center.z);

	float k = (float) (radius / height);
	k = k*k;

	////Derive the coefficients of the quadratic equation
	double a = pow(xd, 2) - k *pow(yd, 2)  +  pow(zd, 2);
	double b = 2 * (diff.x * xd - k * diff.y * yd  + (diff.z) * zd);

	double c = pow(diff.x,2) - k* pow(diff.y,2) + pow(diff.z,2);


	//float a = xd * xd + yd * yd - k * zd * zd;
	//float b = 2 * (xd * diff.x + yd * diff.y -k * zd * (diff.z - height));
	//float c = diff.x * diff.x + diff.y * diff.y - k * (diff.z - height) * (diff.z - height);

	float disc = (float) (b*b - 4 * a*c);

	if (disc < 0.0)
	{
		return false;
	}

	double t;

	if (a == 0)
	{
		t = -c / b;
	}
	else
	{
		float ds = sqrtf(disc);

		t = (-b - ds) / 2.0*a;
		if (t <= 0)
			t = (-b + ds) / 2.0*a;
	}

	hit->obj = this;
	hit->t = t;
	hit->p.x = ray.P.x + t * ray.D.x;
	hit->p.y = ray.P.y + t * ray.D.y;
	hit->p.z = ray.P.z + t * ray.D.z;
	hit->p.w = 1.0;
	//xn = 2 * A*xi + D*yi + E*zi + G
	//	yn = 2 * B*yi + D*xi + F*zi + H
	//	z n = 2 * C*zi + E*xi + F*yi + I
	hit->n.x = 2 * hit->p.x;
	hit->n.y = - 2 * k * hit->p.y; 
	hit->n.z = 2 * hit->p.z;
	hit->n.normalise();
	return true;

}