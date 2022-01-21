#pragma once

#include "mathematics.hpp"
#include "box.hpp"

class CameraCollisionDetector final
{
public:
	const bool checkX(const fvec3& aabbPosition, const fvec3& aabbSize, const fvec3& boxMiddle, const fvec3& boxMiddleChange, Box box) const;
	const bool checkY(const fvec3& aabbPosition, const fvec3& aabbSize, const fvec3& boxMiddle, const fvec3& boxMiddleChange, Box box) const;
	const bool checkZ(const fvec3& aabbPosition, const fvec3& aabbSize, const fvec3& boxMiddle, const fvec3& boxMiddleChange, Box box) const;

private:
	const bool _isInside(const fvec3& aabbPosition, const fvec3& aabbHalfSize, const fvec3& boxMiddle, Box box) const;
};