// Object - The base class for objects.
#include "stdafx.h"
#include <math.h>

#include "object.h"

Object::Object(void)
{
}

void Object::link(Object *obj)
{
	obj_next = obj;
}

Object *Object::next(void)
{
	return obj_next;
}

void Object::setMaterial(Material *m)
{
	obj_mat = m;
}


Colour Object::getColour()
{
	Colour a;
	return a;
}

bool Object::sintersect(Ray &ray, Hit *h, double tl)
{
	bool res;
	Hit nh;

	if (this->intersect(ray, &nh) == true)
	{
		if (nh.t > tl) return false;

		*h = nh;

		return true;
	}

	return false;
}

bool Object::SolveQuadratic(float a, float b, float c)
{
	float disc = b*b - 4 * a*c;
	
	// if discriminant is negative there are no real roots, so return
	// false as ray misses sphere
	if (disc < 0.0)
	{
		return false;
	}
	
	// compute q
	float ds = sqrtf(disc);
	double q;

	if (b < 0.0)
	{
		q = (-b - ds) / 2.0;
	}
	else
	{
		q = (-b + ds) / 2.0;
	}

	// compute t0 and t1
	t0 = q / a;
	t1 = c / q;

	return true;
}
