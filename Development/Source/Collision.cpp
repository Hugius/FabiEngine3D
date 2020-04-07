#include <WE3D/Collision.hpp>

Collision::Collision(bool x, bool y, bool z) :
	p_x(x), p_y(y), p_z(z)
{

}

void Collision::operator+=(const Collision& c)
{
	p_x += c.xCollided();
	p_y += c.yCollided();
	p_z += c.zCollided();

	if (p_x > 1) p_x = 1;
	if (p_y > 1) p_y = 1;
	if (p_z > 1) p_z = 1;
}

void Collision::setX(bool val)
{ 
	p_x = val;
}

void Collision::setY(bool val)
{
	p_y = val;
}

void Collision::setZ(bool val)
{ 
	p_z = val; 
}

inline bool Collision::xCollided() const
{ 
	return p_x;
}

inline bool Collision::yCollided() const
{
	return p_y; 
}

inline bool Collision::zCollided() const
{ 
	return p_z;
}