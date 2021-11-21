#pragma once

#include "mathematics.hpp"

class Ray final
{
public:
	Ray(fvec3 position, fvec3 direction);

	// Vectors
	const fvec3 getPosition() const;
	const fvec3 getDirection() const;

private:
	// Vectors
	fvec3 _position;
	fvec3 _direction;
};