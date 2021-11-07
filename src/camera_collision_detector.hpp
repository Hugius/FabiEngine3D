#pragma once

#include "mathematics.hpp"
#include "box.hpp"

class CameraCollisionDetector final
{
public:
	// Booleans
	const bool checkX(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box) const;
	const bool checkY(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box) const;
	const bool checkZ(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box) const;

private:
	// Booleans
	const bool _isInside(Vec3 aabbPosition, Vec3 aabbHalfSize, Vec3 boxMiddle, Box box) const;
};