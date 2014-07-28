#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "matrix.h"
#include "vertex.h"
class Vertex;

class Vector {
private:
	
public: 
	double x, y, z;

	//Constructors
	Vector(void);
	Vector(double x, double y, double z);
	Vector(const Vertex &v);

	//Class Methods
	double magnitude(void);
	Vector negative(void);
	void normalise(void);
	double dot(const Vector &b);
	Vector cross(const Vector &b);
	Vector reflect(Vector& normal,Vector& incident);

	Vector operator=(const Vector &rhs);
	Vector operator+(const double scalar);
	Vector operator+(const Vector &b);
	Vector operator-(const Vector &b);
	Vector operator*(const double scalar);

};

Vector operator* (const Matrix& mat, const Vector& v);
#endif
