#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string.h>

// matrix is a 4 x 4 square matrix that is used to represent affine transformations

class Matrix {
public:
	double m[4][4]; //array
	
	Matrix(void);
	Matrix(const Matrix &othermat);
	Matrix(double sm[4][4]);
	Matrix(double t00, double t01, double t02, double t03,
		double t10, double t11, double t12, double t13,
		double t20, double t21, double t22, double t23,
		double t30, double t31, double t32, double t33);
	
	Matrix transpose() const;

	~Matrix(void);

	void set_identity(void);

	Matrix& operator= (const Matrix &rhs);

	Matrix operator* (const Matrix &mat) const;

	Matrix operator/ (const double d);


};

#endif