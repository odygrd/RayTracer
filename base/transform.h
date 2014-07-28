#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "matrix.h"
#include "vector.h"
#include "algebra.h"
#include "object.h"

class Transform
{
	// Transform Private Data
	
public :
	Matrix m, mInv;
	Transform(void);
	Transform(const Matrix &smat, const Matrix &sminv);

};

void Translate(const Vector &delta, Object *ob);
void Scale(double x, double y, double z, Object *ob);
void RotateX(float angle, Object *ob);
void RotateY(float angle, Object *ob);
void RotateZ(float angle, Object *ob);

#endif