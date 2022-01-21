#include "box.hpp"

#include <algorithm>

using std::max;

Box::Box(const fvec3& position, float left, float right, float bottom, float top, float back, float front)
	:
	_position(position),
	_left(max(0.0f, left)),
	_right(max(0.0f, right)),
	_bottom(max(0.0f, bottom)),
	_top(max(0.0f, top)),
	_back(max(0.0f, back)),
	_front(max(0.0f, front))
{

}

Box::Box(float left, float right, float bottom, float top, float back, float front)
	:
	_position(fvec3(0.0f)),
	_left(max(0.0f, left)),
	_right(max(0.0f, right)),
	_bottom(max(0.0f, bottom)),
	_top(max(0.0f, top)),
	_back(max(0.0f, back)),
	_front(max(0.0f, front))
{

}

const fvec3& Box::getPosition() const
{
	return _position;
}

const float Box::getLeft() const
{
	return _left;
}

const float Box::getRight() const
{
	return _right;
}

const float Box::getBottom() const
{
	return _bottom;
}

const float Box::getTop() const
{
	return _top;
}

const float Box::getBack() const
{
	return _back;
}

const float Box::getFront() const
{
	return _front;
}