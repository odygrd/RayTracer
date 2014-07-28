#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "object.h"
#include <math.h>

class Cylinder : public Object
{
	Vertex center;
public: 
	Cylinder(Vertex pcenter);
	bool intersect(Ray &ray, Hit *hit);
};

#endif