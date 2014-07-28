#include "stdafx.h"
#include "vertex.h"

Vertex::Vertex(void)
: x(0.0), y(0.0), z(0.0), w(0.0)
{}

Vertex::Vertex(double px, double py, double pz, double pw)
: x(px), y(py), z(pz), w(pw)
{}

// distance between two points
double Vertex::distance(const Vertex& p) const {
	return (sqrt((x - p.x) * (x - p.x)
		+ (y - p.y) * (y - p.y)
		+ (z - p.z) * (z - p.z)));
}

Vertex Vertex::operator= (const Vertex &rhs)
{
	if (this == &rhs)
		return (*this);

	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;

	return(*this);
}

Vertex Vertex::operator- (const Vertex &rhs)
{
	return(Vertex(x - rhs.x, y - rhs.y, z - rhs.z, w));
}

Vertex Vertex::operator* (const double a)
{
	return(Vertex(x * a, y * a, z * a, w));
}

//multiply ray origin with inverse transform matrix
Vertex operator* (const Matrix& mat, const Vertex &p) {
	return (Vertex(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3] * p.w,
		mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3] * p.w,
		mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3] * p.w, 
		1));
}

