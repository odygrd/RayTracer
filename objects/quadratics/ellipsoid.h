#ifndef _ELLIPSOID_H_
#define _ELLIPSOID_H_

#include "object.h"
#include <math.h>

class Ellipsoid : public Object {
	Vertex center;
	float a;
	float b;
	float c;
	float  radius;
public:
	Ellipsoid(Vertex &pcenter,float pa, float pb, float pc, float pradius);
	bool intersect(Ray &ray, Hit *hit);
};


#endif