#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vertex.h"
#include "vector.h"
#include "colour.h"
#include "ray.h"
#include "hit.h"
#include "colour.h"
#include "material.h"
#include <stack>

class Object {
	Object *obj_next;

protected:
	double t0;
	double t1;
	bool SolveQuadratic(float a, float b, float c);
	
public:
	std::stack <Matrix> transform;
	std::stack <Matrix> transformInv;

	Matrix transfinalInv;
	Matrix transfinal;
	Material *obj_mat;
	Object(void);
	void link(Object *obj);
	Object *next(void);
	void setMaterial(Material *m);
	Colour getColour();
	virtual bool intersect(Ray &ray, Hit *h) { return false; }
	virtual bool sintersect(Ray &ray, Hit *h, double tl);
};


#endif
