#ifndef _PLANE_H_
#define _PLANE_H_

#include "object.h"

class Plane : public Object
{
	Vertex a;
	Vector normal;

	public:
		Plane(void);
		Plane(const Vertex &a, const Vector &n);
		bool intersect(Ray &ray, Hit *hit);
};
#endif