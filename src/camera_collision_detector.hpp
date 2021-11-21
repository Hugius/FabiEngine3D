#pragma once

#include "mathematics.hpp"
#include "box.hpp"

class CameraCollisionDetector final
{
public:
	// Booleans
	const bool checkX(fvec3 aabbPosition, fvec3 aabbSize, fvec3 boxMiddle, fvec3 boxMiddleChange, Box box) const;
	const bool checkY(fvec3 aabbPosition, fvec3 aabbSize, fvec3 boxMiddle, fvec3 boxMiddleChange, Box box) const;
	const bool checkZ(fvec3 aabbPosition, fvec3 aabbSize, fvec3 boxMiddle, fvec3 boxMiddleChange, Box box) const;

private:
	// Booleans
	const bool _isInside(fvec3 aabbPosition, fvec3 aabbHalfSize, fvec3 boxMiddle, Box box) const;
};