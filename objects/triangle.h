#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object.h"

class Triangle :public Object
{
	Vertex v0, v1, v2;
	Vector normal;
public:
	Triangle(void);
	Triangle(const Vertex &a, const Vertex &b, const Vertex &c);
	void calc_normal(void);
	bool intersect(Ray &ray, Hit *hit);
};

#endif