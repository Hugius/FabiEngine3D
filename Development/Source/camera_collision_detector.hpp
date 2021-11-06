#pragma once

#include "mathematics.hpp"
#include "box.hpp"

class CameraCollisionDetector final
{
public:
	// Booleans
	bool checkX(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box);
	bool checkY(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box);
	bool checkZ(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box);

private:
	// Booleans
	bool _isInside(Vec3 aabbPosition, Vec3 aabbHalfSize, Vec3 boxMiddle, Box box);
};