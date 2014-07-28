#include "stdafx.h"
#include "matrix.h"

//default constructor - identity matrix
Matrix::Matrix(void) {
	memset(m, 0.0, 16 * sizeof (double));
	m[0][0] = 1.0;
	m[1][1] = 1.0;
	m[2][2] = 1.0;
	m[3][3] = 1.0;
}

//copy constructor
Matrix::Matrix(const Matrix &othermat)
{
	memcpy(m, othermat.m, 16 * sizeof (double));
}

Matrix::Matrix(double sm[4][4])
{
	memcpy(m, sm, 16 * sizeof (double));
}

Matrix::Matrix(double t00, double t01, double t02, double t03,
	double t10, double t11, double t12, double t13,
	double t20, double t21, double t22, double t23,
	double t30, double t31, double t32, double t33)
{
	m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
	m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
	m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
	m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
}



Matrix::~Matrix(void) {}

Matrix Matrix::transpose() const
{
	return Matrix(m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}

//set to equal
Matrix &Matrix::operator= (const Matrix &rhs)
{
	if (this == &rhs)
		return (*this);

	for (int x = 0; x < 4; x++)
	for (int y = 0; y < 4; y++)
		m[x][y] = rhs.m[x][y];
	return (*this);
}

// multiplication
Matrix Matrix::operator* (const Matrix &mat) const {
	Matrix product;

	for (int y = 0; y < 4; y++)
	for (int x = 0; x < 4; x++)
	{
		double sum = 0.0;
		for (int j = 0; j < 4; j++)
			sum += m[x][j] * mat.m[j][y];

		product.m[x][y] = sum;
	}

	return product;
}

//division
Matrix Matrix::operator/ (const double d)
{
	for (int x = 0; x < 4; x++)
	for (int y = 0; y < 4; y++)
		m[x][y] = m[x][y] / d;

	return (*this);
}

//set to identity
void Matrix::set_identity(void)
{
	for (int x = 0; x < 4; x++)
	for (int y = 0; y < 4; y++)
	{
		if (x == y)
			m[x][y] = 1.0;
		else
			m[x][y] = 0.0;
	}
}