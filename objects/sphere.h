#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "object.h"
#include "transform.h"

class Sphere : public Object {
	Vertex sp;
	float  r;
public:
	Sphere(Vertex &psp, float pr);
	bool intersect(Ray &ray, Hit *hit);
};

#endif
