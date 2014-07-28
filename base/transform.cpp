#include "stdafx.h"
#include "transform.h"
#include <cmath>


Transform::Transform()
:m(Matrix()), mInv(Matrix())
{}

Transform::Transform(const Matrix &smat, const Matrix &smInv)
: m(smat), mInv(smInv)
{}


void Translate(const Vector &delta,Object *ob) {
	Matrix m, minv;
	m = Matrix(1, 0, 0, delta.x,
		0, 1, 0, delta.y,
		0, 0, 1, delta.z,
		0, 0, 0, 1);
	minv = Matrix(1, 0, 0, -delta.x,
		0, 1, 0, -delta.y,
		0, 0, 1, -delta.z,
		0, 0, 0, 1);
	ob->transform.push(m);
	ob->transformInv.push(minv);
}

void Scale(double x, double y, double z, Object *ob) {
	Matrix m, minv;
	m = Matrix(x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
	minv = Matrix(1.0 / x, 0, 0, 0,
		0, 1.0 / y, 0, 0,
		0, 0, 1.0 / z, 0,
		0, 0, 0, 1);
	ob->transform.push(m);
	ob->transformInv.push(minv);
}

void RotateX(float angle, Object *ob) {
	float sin_t = sinf((float)Radians(angle));
	float cos_t = cosf((float)Radians(angle));
	Matrix m = Matrix(1, 0, 0, 0,
		0, cos_t, -sin_t, 0,
		0, sin_t, cos_t, 0,
		0, 0, 0, 1);
	ob->transform.push(m);
	ob->transformInv.push(m);
}
void RotateY(float angle, Object *ob) {
	double sin_t = sinf((float)Radians(angle));
	double cos_t = cosf((float)Radians(angle));
	Matrix m = Matrix(cos_t, 0, sin_t, 0,
		0, 1, 0, 0,
		-sin_t, 0, cos_t, 0,
		0, 0, 0, 1);
	ob->transform.push(m);
	ob->transformInv.push(m);
}

void RotateZ(float angle, Object *ob) {
	double sin_t = sinf((float)Radians(angle));
	double cos_t = cosf((float)Radians(angle));
	Matrix m = Matrix(cos_t, -sin_t, 0, 0,
		sin_t, cos_t, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	ob->transform.push(m);
	ob->transformInv.push(m);
}