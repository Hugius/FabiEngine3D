#include "collision.hpp"

Collision::Collision(bool x, bool y, bool z) :
	_x(x), _y(y), _z(z)
{

}

void Collision::operator+=(const Collision& c)
{
	_x += c.xCollided();
	_y += c.yCollided();
	_z += c.zCollided();

	if (_x > 1) { _x = 1; }
	if (_y > 1) { _y = 1; }
	if (_z > 1) { _z = 1; }
}

void Collision::setX(bool value)
{ 
	_x = value;
}

void Collision::setY(bool value)
{
	_y = value;
}

void Collision::setZ(bool value)
{ 
	_z = value; 
}

inline bool Collision::xCollided() const
{ 
	return _x;
}

inline bool Collision::yCollided() const
{
	return _y; 
}

inline bool Collision::zCollided() const
{ 
	return _z;
}