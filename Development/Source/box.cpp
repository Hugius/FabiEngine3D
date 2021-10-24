#include "box.hpp"

#include <algorithm>

using std::max;

Box::Box(float left, float right, float bottom, float top, float front, float back) :
	_left(max(0.0f, (left * 0.99f))),
	_right(max(0.0f, (right * 0.99f))),
	_bottom(max(0.0f, (bottom * 0.99f))),
	_top(max(0.0f, (top * 0.99f))),
	_front(max(0.0f, (front * 0.99f))),
	_back(max(0.0f, (back * 0.99f)))
{

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

const float Box::getFront() const
{
	return _front;
}

const float Box::getBack() const
{
	return _back;
}