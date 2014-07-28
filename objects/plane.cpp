//plane object
#include "stdafx.h"
#include <math.h>

#include "plane.h"

Plane::Plane(void)
	: a(Vertex(0, 0, 0, 1)), normal(Vector(0, 1, 0))
{}

Plane::Plane(const Vertex &pa, const Vector &pn)
: a(Vertex(pa.x, pa.y, pa.z, pa.w)), normal(Vector(pn.x, pn.y, pn.z))
{}

bool Plane::intersect(Ray &ray, Hit *hit)
{
	Vector d(a.x - ray.P.x, a.y - ray.P.y, a.z - ray.P.z); //find the vector between the plane point and the ray origin
	double t = d.dot(normal) / ray.D.dot(normal); //calculate t

	if (t < 0.0001)
	{
		return (false);
	}

		hit->obj = this;
		hit->t = t;

		hit->p.x = ray.P.x + t * ray.D.x;
		hit->p.y = ray.P.y + t * ray.D.y;
		hit->p.z = ray.P.z + t * ray.D.z;
		hit->p.w = 1.0;
		hit->n.x = normal.x;
		hit->n.y = normal.y;
		hit->n.z = normal.z;
		hit->n.normalise();

	return (true);
}