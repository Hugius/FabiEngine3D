#pragma once

#include "mathematics.hpp"

class Ray final
{
public:
	Ray(Vec3 position, Vec3 direction);

	const Vec3 getPosition() const;
	const Vec3 getDirection() const;

private:
	Vec3 _position;
	Vec3 _direction;
};