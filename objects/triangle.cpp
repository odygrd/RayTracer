#include "stdafx.h"
#include "triangle.h"

Triangle::Triangle(void)
{
	v0 = Vertex(0, 0, 0, 0);
	v1 = Vertex(0, 0, 1, 0);
	v2 = Vertex(0, 1, 0, 0);
	normal = Vector(0, 1, 0);
}

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
{
	v0 = a;
	v1 = b;
	v2 = c;
	calc_normal();
}

void Triangle::calc_normal(void)
{
	Vector a(v1.x-v0.x,v1.y-v0.y,v1.z-v0.z);
	Vector b(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

	normal = a.cross(b);
	normal.normalise();
}

bool Triangle::intersect(Ray &ray, Hit *hit)
{

	Vector edge1(v1.x -v0.x, v1.y - v0.y, v1.z - v0.z);
	Vector edge2(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

	Vector pvec = ray.D.cross(edge2);

	float det = edge1.dot(pvec);
	if (det == 0) return false; //ray misses

	float invDet = 1 / det;

	//compute u and reject the triangle if u is either lower than 0 or greater than 1
	Vector tvec = ray.P - v0;
	float u = tvec.dot(pvec) * invDet; 
	if (u < 0 || u > 1) return false;

	//compute v and apply the tests
	//there's no intersection if v is lower than 0 or greater than 1 and if u+v is greater than 1
	Vector qvec = tvec.cross(edge1); 
	float v = ray.D.dot(qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	//compute t,ray intersects triangle
	double t = edge2.dot(qvec) * invDet;

	hit->obj = this;
	hit->t = t;

	hit->p.x = ray.P.x + t * ray.D.x;
	hit->p.y = ray.P.y + t * ray.D.y;
	hit->p.z = ray.P.z + t * ray.D.z;
	hit->p.w = 1.0;
	hit->n.x = normal.x;
	hit->n.y = normal.y;
	hit->n.z = normal.z;

	return true; // this ray hits the triangle
}



