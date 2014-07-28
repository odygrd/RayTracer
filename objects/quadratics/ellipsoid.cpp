#include "stdafx.h"
#include "ellipsoid.h"

Ellipsoid::Ellipsoid(Vertex &pcenter, float pa, float pb, float pc, float pradius)
{
	center = pcenter;
	a = pa;
	b = pb;
	c = pc;
	radius = pradius;
}

bool Ellipsoid::intersect(Ray &ray, Hit *hit)
{

	double Aq = a* pow(ray.D.x, 2) + b * pow(ray.D.y, 2) + c * pow(ray.D.z, 2);

	double	Bq = 2 * a * (ray.P.x - center.x)*ray.D.x + 2 * b * ( ray.P.y - center.y)*ray.D.y + 2 * c * (ray.P.z - center.z)*ray.D.z;

	double	Cq = a * pow((ray.P.x - center.x), 2) + b * pow((ray.P.y - center.y), 2) + c * pow((ray.P.z - center.z), 2) - radius;

	if (!Object::SolveQuadratic(Aq, Bq, Cq))
		return false;

	double t = t0;
	if (t < 0.00001)
		t = t1;


	hit->obj = this;

	hit->t = t;
	hit->p.x = ray.P.x + t * ray.D.x;
	hit->p.y = ray.P.y + t * ray.D.y;
	hit->p.z = ray.P.z + t * ray.D.z;
	hit->p.w = 1.0;
	//xn = 2 * A*xi + D*yi + E*zi + G
	//	yn = 2 * B*yi + D*xi + F*zi + H
	//	z n = 2 * C*zi + E*xi + F*yi + I
	hit->n.x = 2 * a * hit->p.x - center.x;
	hit->n.y = 2 * b * hit->p.y - center.y;
	hit->n.z = 2 * c * hit->p.z - center.z;
	hit->n.normalise();
	return true;

}