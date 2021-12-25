#pragma once

#include "mathematics.hpp"

class Ray final
{
public:
	Ray(fvec3 position, fvec3 direction);

	const fvec3 getPosition() const;
	const fvec3 getDirection() const;

private:
	fvec3 _position;
	fvec3 _direction;
};