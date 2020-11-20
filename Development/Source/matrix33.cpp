#include "matrix33.hpp"

// Create the matrix with specified values
Matrix33::Matrix33(
	float m00, float m01, float m02, 
	float m10, float m11, float m12, 
	float m20, float m21, float m22)
{
	this->m[0][0] = m00; this->m[1][0] = m10; this->m[2][0] = m20;
	this->m[0][1] = m01; this->m[1][1] = m11; this->m[2][1] = m21;
	this->m[0][2] = m02; this->m[1][2] = m12; this->m[2][2] = m22;
}

// Create the identity matrix
Matrix33::Matrix33()
{
	for (int i = 0; i < 9; i++) {
		f[i] = 0.0f;
	}

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
}

// Create a matrix from another bigger matrix
Matrix33::Matrix33(const Matrix44& mat)
{
	this->m[0][0] = mat.m[0][0]; this->m[1][0] = mat.m[1][0]; this->m[2][0] = mat.m[2][0];
	this->m[0][1] = mat.m[0][1]; this->m[1][1] = mat.m[1][1]; this->m[2][1] = mat.m[2][1];
	this->m[0][2] = mat.m[0][2]; this->m[1][2] = mat.m[1][2]; this->m[2][2] = mat.m[2][2];
}

// Create a custom identity matrix
Matrix33::Matrix33(float value)
{
	for (int i = 0; i < 9; i++) {
		f[i] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
}

// Matrix-matrix addition
Matrix33 Matrix33::operator+(const Matrix33& mat) const
{
	Matrix33 newMatrix;

	for (int i = 0; i < 9; i++) {
		newMatrix.f[i] = this->f[i] + mat.f[i];
	}

	return newMatrix;
}

// Matrix-matrix subtraction
Matrix33 Matrix33::operator-(const Matrix33& mat) const
{
	Matrix33 newMatrix;

	for (int i = 0; i < 9; i++) {
		newMatrix.f[i] = this->f[i] - mat.f[i];
	}

	return newMatrix;
}

// Matrix-matrix multiplication
Matrix33 Matrix33::operator*(const Matrix33& mat) const
{
	Matrix33 newMatrix(0.0f);

	for (int column = 0; column < 3; column++) {
		for (int row = 0; row < 3; row++) {
			for (int inner = 0; inner < 3; inner++) {
				newMatrix.m[row][column] += this->m[inner][column] * mat.m[row][inner];
			}
		}
	}

	return newMatrix;
}