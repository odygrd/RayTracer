#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "vector.h"
#include "matrix.h"

#include <math.h>

class Vertex {
public:
	double x;
	double y;
	double z;
	double w;
	Vertex(void);
	Vertex(double px, double py, double pz, double pw);
	
	double distance(const Vertex& p) const;

	Vertex operator=(const Vertex &rhs);
	Vertex operator-(const Vertex &rhs);
	Vertex operator*(const double a);
	
};

Vertex operator* (const Matrix &mat, const Vertex &p);

#endif
