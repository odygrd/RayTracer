#include "stdafx.h"
#include "qsphere.h"

// Sphere defined as vertex (in world space) and radius

QSphere::QSphere(Vertex &pcenter, float pradius)
{
	center = pcenter;
	radius = pradius;
}

bool QSphere::intersect(Ray &ray, Hit *hit)
{

	double Aq = pow(ray.D.x, 2) + pow(ray.D.y, 2) + pow(ray.D.z, 2);

	double	Bq = 2 * (ray.P.x - center.x)*ray.D.x + 2 * (ray.P.y - center.y)*ray.D.y + 2 * (ray.P.z - center.z)*ray.D.z;

	double	Cq = pow((ray.P.x - center.x), 2) + pow((ray.P.y - center.y), 2) + pow((ray.P.z - center.z), 2) - radius;

	float disc = (float) (Bq*Bq - 4 * Aq*Cq);

	// if discriminant is negative there are no real roots, so return
	// false as ray misses sphere
	if (disc < 0.0)
	{
		return false;
	}

	// compute q
	float ds = sqrtf(disc);
	double q;

	if (Bq < 0.0)
	{
		q = (-Bq - ds) / 2.0;
	}
	else
	{
		q = (-Bq + ds) / 2.0;
	}

	// compute t0 and t1
	double t = q / Aq;
	if (t<0.00001)
		t = Cq / q;

	hit->obj = this;
	hit->t = t;
	hit->p.x = ray.P.x + t * ray.D.x;
	hit->p.y = ray.P.y + t * ray.D.y;
	hit->p.z = ray.P.z + t * ray.D.z;
	hit->p.w = 1.0;
	//xn = 2 * A*xi + D*yi + E*zi + G
	//	yn = 2 * B*yi + D*xi + F*zi + H
	//	z n = 2 * C*zi + E*xi + F*yi + I
	hit->n.x = 2 * hit->p.x - center.x;
	hit->n.y = 2 * hit->p.y - center.y;
	hit->n.z = 2 * hit->p.z - center.z;
	hit->n.normalise();
	return true;

}