#include "stdafx.h"
#include "ray.h"

Ray::Ray()
	: P(Vertex(0.0, 0.0, 0.0, 0.0)), D(Vector(1, 0, 0))
{}

Ray::Ray(Vertex pp, Vector pd)
	: P(pp), D(pd)
{}

Vertex Ray::position(double t)
{
	Vertex v;

	v.x = P.x + t * D.x;
	v.y = P.y + t * D.y;
	v.z = P.z + t * D.z;
	v.w = P.w;

	return v;
}
