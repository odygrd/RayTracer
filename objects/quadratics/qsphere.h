#ifndef _QSPHERE_H_
#define _QSPHERE_H_

#include "object.h"
#include <math.h>

class QSphere : public Object {
	Vertex center;
	float  radius;
public:
	QSphere(Vertex &pcenter, float pradius);
	QSphere(Vertex &psp, float pr, Material m);
	bool intersect(Ray &ray, Hit *hit);
};


#endif