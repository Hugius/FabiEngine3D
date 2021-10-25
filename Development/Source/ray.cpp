#include "ray.hpp"

Ray::Ray(Vec3 position, Vec3 direction) :
	_position(position),
	_direction(direction)
{

}

const Vec3 Ray::getPosition() const
{
	return _position;
}

const Vec3 Ray::getDirection() const
{
	return _direction;
}
