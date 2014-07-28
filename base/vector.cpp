#include "stdafx.h"
#include <math.h>
#include "vector.h"

Vector::Vector(void) 
	: x(0.0), y(0.0), z(0.0)
{}

Vector::Vector(double px, double py, double pz)
	: x(px), y(py), z(pz)
{}

Vector::Vector(const Vertex &v)
	: x(v.x), y(v.y), z(v.z)
{}

double Vector::magnitude()
{
	return sqrt((x*x) + (y*y) + (z*z));
}

void Vector::normalise(void)
{
	double magnitude = sqrt((x*x) + (y*y) + (z*z));
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

Vector Vector::negative(void)
{
	return Vector(-x, -y, -z);
}

double Vector::dot(const Vector &b)
{
	return (x*b.x) + (y*b.y) + (z*b.z);
}

Vector Vector::cross(const Vector &b)
{
	return Vector(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
}

Vector Vector::reflect(Vector& normal,Vector& incident)
{
	const double cosI = -normal.dot(incident);
	Vector relf = (incident + normal * cosI * 2.0);
	relf.normalise();
	return relf;
}


Vector Vector::operator=(const Vector &rhs)
{
	if (this == &rhs)
		return (*this);

	x = rhs.x; 
	y = rhs.y; 
	z = rhs.z;

	return (*this);
}


Vector Vector::operator*(const double scalar)
{
	return (Vector(x*scalar, y*scalar, z*scalar));
}

Vector Vector::operator-(const Vector &b)
{
	return Vector(x - b.x, y - b.y, z - b.z);
}

Vector Vector::operator+(const Vector &b)
{
	return Vector(x + b.x, y + b.y, z + b.z);
}

Vector Vector::operator+(const double scalar)
{
	return Vector(x + scalar, y + scalar, z + scalar);
}
//transform the ray direction
Vector operator* (const Matrix &mat, const Vector &v) {
	return (Vertex(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
		mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
		mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z,
		0));
}
