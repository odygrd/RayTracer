#ifndef _RAY_H_
#define _RAY_H_

#include "vertex.h"
#include "vector.h"

class Ray {
public:
	Ray();
	Ray(Vertex p, Vector d);

	Vertex P; //ray origin
	Vector D; //ray direction
	Vertex position(double t);
};


#endif
