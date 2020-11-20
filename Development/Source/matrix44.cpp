#include "matrix44.hpp"
#include "matrix33.hpp"

/* --------------------------------------------------= MEMBER FUNCTIONS =-------------------------------------------------- */

// Create the matrix with specified values
Matrix44::Matrix44(
	float m00, float m01, float m02, float m03, 
	float m10, float m11, float m12, float m13, 
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	this->m[0][0] = m00; this->m[1][0] = m10; this->m[2][0] = m20; this->m[3][0] = m30;
	this->m[0][1] = m01; this->m[1][1] = m11; this->m[2][1] = m21; this->m[3][1] = m31;
	this->m[0][2] = m02; this->m[1][2] = m12; this->m[2][2] = m22; this->m[3][2] = m32;
	this->m[0][3] = m03; this->m[1][3] = m13; this->m[2][3] = m23; this->m[3][3] = m33;
}

float Matrix44::operator[](unsigned int index) const
{
	return this->f[index];
}

// Create the identity matrix
Matrix44::Matrix44()
{
	for (int i = 0; i < 16; i++) {
		f[i] = 0.0f;
	}

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
}

// Create a custom identity matrix
Matrix44::Matrix44(float value)
{
	for (int i = 0; i < 16; i++) {
		f[i] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
	this->m[3][3] = value;
}

// Create a matrix from another smaller matrix
Matrix44::Matrix44(const Matrix33& mat)
{
	this->m[0][0] = mat.m[0][0]; this->m[1][0] = mat.m[1][0]; this->m[2][0] = mat.m[2][0]; this->m[3][0] = 0.0f;
	this->m[0][1] = mat.m[0][1]; this->m[1][1] = mat.m[1][1]; this->m[2][1] = mat.m[2][1]; this->m[3][1] = 0.0f;
	this->m[0][2] = mat.m[0][2]; this->m[1][2] = mat.m[1][2]; this->m[2][2] = mat.m[2][2]; this->m[3][2] = 0.0f;
	this->m[0][3] = 0.0f; this->m[1][3] = 0.0f; this->m[2][3] = 0.0f; this->m[3][3] = 1.0f;
}

// Matrix-vector3 multiplication
Vec3 Matrix44::operator*(const Vec3& vec) const
{
	Vec3 newVector;

	newVector.x = this->m[0][0] * vec.x + this->m[1][0] * vec.y + this->m[2][0] * vec.z + this->m[3][0] * 1.0f;
	newVector.y = this->m[0][1] * vec.x + this->m[1][1] * vec.y + this->m[2][1] * vec.z + this->m[3][1] * 1.0f;
	newVector.z = this->m[0][2] * vec.x + this->m[1][2] * vec.y + this->m[2][2] * vec.z + this->m[3][2] * 1.0f;

	return newVector;

}

// Matrix-vector4 multiplication
Vec4 Matrix44::operator*(const Vec4& vec) const
{
	Vec4 newVector;

	newVector.x = this->m[0][0] * vec.x + this->m[1][0] * vec.y + this->m[2][0] * vec.z + this->m[3][0] * vec.w;
	newVector.y = this->m[0][1] * vec.x + this->m[1][1] * vec.y + this->m[2][1] * vec.z + this->m[3][1] * vec.w;
	newVector.z = this->m[0][2] * vec.x + this->m[1][2] * vec.y + this->m[2][2] * vec.z + this->m[3][2] * vec.w;
	newVector.w = this->m[0][3] * vec.x + this->m[1][3] * vec.y + this->m[2][3] * vec.z + this->m[3][3] * vec.w;

	return newVector;

}

// Matrix-matrix addition
Matrix44 Matrix44::operator+(const Matrix44& mat) const
{
	Matrix44 newMatrix;

	for (int i = 0; i < 16; i++) {
		newMatrix.f[i] = this->f[i] + mat.f[i];
	}

	return newMatrix;
}

// Matrix-matrix subtraction
Matrix44 Matrix44::operator-(const Matrix44& mat) const
{
	Matrix44 newMatrix;

	for (int i = 0; i < 16; i++) {
		newMatrix.f[i] = this->f[i] - mat.f[i];
	}

	return newMatrix;
}

// Matrix-matrix multiplication
Matrix44 Matrix44::operator*(const Matrix44& mat) const
{
	Matrix44 newMatrix(0.0f);

	for (int column = 0; column < 4; column++) {
		for (int row = 0; row < 4; row++) {
			for (int inner = 0; inner < 4; inner++) {
				newMatrix.m[row][column] += this->m[inner][column] * mat.m[row][inner];
			}
		}
	}

	return newMatrix;
}

// Return X axis of the matrix
Vec3 Matrix44::GetXAxis() const
{
	Vec3 newVector;
	newVector.x = this->m[0][0];
	newVector.y = this->m[0][1];
	newVector.z = this->m[0][2];

	return newVector;
}

// Return Y axis of the matrix
Vec3 Matrix44::GetYAxis() const
{
	Vec3 newVector;

	newVector.x = this->m[1][0];
	newVector.y = this->m[1][1];
	newVector.z = this->m[1][2];

	return newVector;
}

// Return Z axis of the matrix
Vec3 Matrix44::GetZAxis() const
{
	Vec3 newVector;

	newVector.x = this->m[2][0];
	newVector.y = this->m[2][1];
	newVector.z = this->m[2][2];

	return newVector;
}

// Return the determinant of the matrix
float Matrix44::getDeterminant() const
{
	float determinant = 0.0f;
	float values[4];

	values[0] = this->m[0][0] * ((this->m[1][1] * ((this->m[2][2] * this->m[3][3]) - (this->m[2][3] * this->m[3][2]))) - (this->m[1][2] * ((this->m[2][1] * this->m[3][3]) - (this->m[2][3] * this->m[3][1]))) + (this->m[1][3] * ((this->m[2][1] * this->m[3][2]) - (this->m[2][2] * this->m[3][1]))));
	values[1] = this->m[0][1] * ((this->m[1][0] * ((this->m[2][2] * this->m[3][3]) - (this->m[2][3] * this->m[3][2]))) - (this->m[1][2] * ((this->m[2][0] * this->m[3][3]) - (this->m[2][3] * this->m[3][0]))) + (this->m[1][3] * ((this->m[2][0] * this->m[3][2]) - (this->m[2][2] * this->m[3][0]))));
	values[2] = this->m[0][2] * ((this->m[1][0] * ((this->m[2][1] * this->m[3][3]) - (this->m[2][3] * this->m[3][1]))) - (this->m[1][1] * ((this->m[2][0] * this->m[3][3]) - (this->m[2][3] * this->m[3][0]))) + (this->m[1][3] * ((this->m[2][0] * this->m[3][1]) - (this->m[2][1] * this->m[3][0]))));
	values[3] = this->m[0][3] * ((this->m[1][0] * ((this->m[2][1] * this->m[3][2]) - (this->m[2][2] * this->m[3][1]))) - (this->m[1][1] * ((this->m[2][0] * this->m[3][2]) - (this->m[2][2] * this->m[3][0]))) + (this->m[1][2] * ((this->m[2][0] * this->m[3][1]) - (this->m[2][1] * this->m[3][0]))));
	determinant = (values[0] - values[1] + values[2] - values[3]);

	return determinant;
}

// Invert the matrix
bool Matrix44::invert()
{
	float determinant = this->getDeterminant();
	if (determinant == 0.0f) // Check if determinant is valid
	{ 
		// Unsuccessful inversion
		return false;
	}
	else 
	{
		// Declare variables
		Matrix44 newMatrix;
		float a = m[0][0], b = m[0][1], c = m[0][2], d = m[0][3];
		float e = m[1][0], f = m[1][1], g = m[1][2], h = m[1][3];
		float i = m[2][0], j = m[2][1], k = m[2][2], l = m[2][3];
		float mm = m[3][0], n = m[3][1], o = m[3][2], p = m[3][3];

		// Calculate matrix of minors
		newMatrix.m[0][0] = (f * (k*p - o * l) - g * (j*p - n * l) + h * (j*o - n * k));
		newMatrix.m[0][1] = (e * (k*p - o * l) - g * (i*p - mm * l) + h * (i*o - mm * k));
		newMatrix.m[0][2] = (e * (j*p - n * l) - f * (i*p - mm * l) + h * (i*n - mm * j));
		newMatrix.m[0][3] = (e * (j*o - n * k) - f * (i*o - mm * k) + g * (i*n - mm * j));

		newMatrix.m[1][0] = (b * (k*p - o * l) - c * (j*p - n * l) + d * (j*o - n * k));
		newMatrix.m[1][1] = (a * (k*p - o * l) - c * (i*p - mm * l) + d * (i*o - mm * k));
		newMatrix.m[1][2] = (a * (j*p - n * l) - b * (i*p - mm * l) + d * (i*n - mm * j));
		newMatrix.m[1][3] = (a * (j*o - n * k) - b * (i*o - mm * k) + c * (i*n - mm * j));

		newMatrix.m[2][0] = (b * (g*p - o * h) - c * (f*p - n * h) + d * (f*o - n * g));
		newMatrix.m[2][1] = (a * (g*p - o * h) - c * (e*p - mm * h) + d * (e*o - mm * g));
		newMatrix.m[2][2] = (a * (f*p - n * h) - b * (e*p - mm * h) + d * (e*n - mm * f));
		newMatrix.m[2][3] = (a * (f*o - n * g) - b * (e*o - mm * g) + c * (e*n - mm * f));

		newMatrix.m[3][0] = (b * (g*l - k * h) - c * (f*l - j * h) + d * (f*k - j * g));
		newMatrix.m[3][1] = (a * (g*l - k * h) - c * (e*l - i * h) + d * (e*k - i * g));
		newMatrix.m[3][2] = (a * (f*l - j * h) - b * (e*l - i * h) + d * (e*j - f * i));
		newMatrix.m[3][3] = (a * (f*k - j * g) - b * (e*k - i * g) + c * (e*j - f * i));

		// Calculate matrix of cofactors
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++) {
				if ((row + column) % 2 == 1) {
					newMatrix.m[row][column] = -newMatrix.m[row][column];
				}
			}
		}

		// Calculate matrix adjugate
		newMatrix.transpose();

		// Multiply resulting matrix by 1 / determinant
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++) {
				newMatrix.m[row][column] = newMatrix.m[row][column] * (1.0f / determinant);
				m[row][column] = newMatrix.m[row][column];
			}
		}

		// Matrix successfully inverted
		return true;
	}
}

// Transpose the matrix
void Matrix44::transpose()
{
	// Copy current matrix to temporary matrix
	Matrix44 tempMatrix;
	for (int i = 0; i < 16; i++) {
		tempMatrix.f[i] = this->f[i];
	}


	// Swap rows and columns
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			this->m[r][c] = tempMatrix.m[c][r];
		}
	}

}

// Set the euler axis of the matrix
void Matrix44::SetEulerAxis(float yaw, float pitch, float roll)
{
	Matrix44 newMatrix;

	Matrix44 yawMatrix = createRotationY(yaw);
	Matrix44 pitchMatrix = createRotationX(pitch);
	Matrix44 rollMatrix = createRotationZ(roll);
	newMatrix = yawMatrix * pitchMatrix * rollMatrix;

	*this = newMatrix;
}

/* --------------------------------------------------= STATIC FUNCTIONS =-------------------------------------------------- */

// Create and return a new translation matrix
Matrix44 Matrix44::createTranslation(float x, float y, float z)
{
	Matrix44 newMatrix;

	newMatrix.m[3][0] = x;
	newMatrix.m[3][1] = y;
	newMatrix.m[3][2] = z;

	return newMatrix;
}

// Create and return a new scaling matrix
Matrix44 Matrix44::createScaling(float x, float y, float z)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = x;
	newMatrix.m[1][1] = y;
	newMatrix.m[2][2] = z;

	return newMatrix;
}

// Create and return a new rotation matrix
Matrix44 Matrix44::createRotation(float x, float y, float z)
{
	Matrix44 newMatrix;

	newMatrix = newMatrix * createRotationX(x);
	newMatrix = newMatrix * createRotationY(y);
	newMatrix = newMatrix * createRotationZ(z);

	return newMatrix;
}

// Create and return a new X rotation matrix
Matrix44 Matrix44::createRotationX(float angle)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[1][0] = -sin(angle);
	newMatrix.m[0][1] = sin(angle);
	newMatrix.m[1][1] = cos(angle);

	return newMatrix;
}

// Create and return a new Y rotation matrix
Matrix44 Matrix44::createRotationY(float angle)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] =  cos(angle);
	newMatrix.m[0][2] = -sin(angle);
	newMatrix.m[2][0] =  sin(angle);
	newMatrix.m[2][2] =  cos(angle);

	return newMatrix;
}

// Create and return a new Z rotation matrix
Matrix44 Matrix44::createRotationZ(float angle)
{
	Matrix44 newMatrix;

	newMatrix.m[1][1] = cos(angle);
	newMatrix.m[1][2] = sin(angle);
	newMatrix.m[2][1] = -sin(angle);
	newMatrix.m[2][2] = cos(angle);

	return newMatrix;
}

// Create and return a new orthographic projection matrix
Matrix44 Matrix44::createOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = 2.0f / (right - left);
	newMatrix.m[1][1] = 2.0f / (top - bottom);
	newMatrix.m[2][2] = -2.0f / (farZ - nearZ);
	newMatrix.m[3][0] = -(right + left) / (right - left);
	newMatrix.m[3][1] = -(top + bottom) / (top - bottom);
	newMatrix.m[3][2] = -(4 * (nearZ) / (farZ - nearZ));

	return newMatrix;
};

// Create and return a new perspective projection matrix
Matrix44 Matrix44::createPerspective(float fovY, float aspect, float nearZ, float farZ)
{
	Matrix44 result;

	result.m[0][0] = 1.0f / (aspect*tan(fovY / 2.0f));
	result.m[1][1] = 1.0f / tan(fovY / 2.0f);
	result.m[2][2] = -(farZ + nearZ) / (farZ - nearZ);
	result.m[2][3] = -1.0f;
	result.m[3][2] = (-2.0f * farZ * nearZ) / (farZ - nearZ);
	
	return result;
}

// Create and return a new view matrix
Matrix44 Matrix44::createLookAt
	(const Vec3 & eye, const Vec3 & center, const Vec3 & up)
{
	// Calculate direction vectors
	Vec3 frontVector = center - eye;
	frontVector.normalize();
	Vec3 rightVector = frontVector.cross(up);
	rightVector.normalize();
	Vec3 upVector = rightVector.cross(frontVector);

	// Create view matrix
	Matrix44 newMatrix;
	newMatrix.m[0][0] = rightVector.x;
	newMatrix.m[1][0] = rightVector.y;
	newMatrix.m[2][0] = rightVector.z;
	newMatrix.m[0][1] = upVector.x;
	newMatrix.m[1][1] = upVector.y;
	newMatrix.m[2][1] = upVector.z;
	newMatrix.m[0][2] = -frontVector.x;
	newMatrix.m[1][2] = -frontVector.y;
	newMatrix.m[2][2] = -frontVector.z;
	newMatrix.m[3][0] = -(rightVector.dot(eye));
	newMatrix.m[3][1] = -(upVector.dot(eye));
	newMatrix.m[3][2] = frontVector.dot(eye);
	return newMatrix;
}