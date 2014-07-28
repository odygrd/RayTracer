#ifndef _CONE_H_
#define _CONE_H_

#include "object.h"
#include <math.h>

class Cone : public Object
{
	Vertex center;
	double radius;
	double height;
public :
	Cone(Vertex c, double r, double h);
	bool intersect(Ray &ray, Hit *hit);
};
#endif