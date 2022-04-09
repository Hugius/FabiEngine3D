#pragma once

#include "mathematics.hpp"

class Ray final
{
public:
	Ray(const fvec3 & position, const fvec3 & direction);

	const fvec3 & getPosition() const;
	const fvec3 & getDirection() const;

private:
	const fvec3 _position;
	const fvec3 _direction;
};