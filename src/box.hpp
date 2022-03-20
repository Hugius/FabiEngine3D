#pragma once

#include "mathematics.hpp"

class Box final
{
public:
	Box(const fvec3& position, float left, float right, float bottom, float top, float back, float front);
	Box(float left, float right, float bottom, float top, float back, float front);

	const fvec3& getPosition() const;

	const float getLeft() const;
	const float getRight() const;
	const float getBottom() const;
	const float getTop() const;
	const float getBack() const;
	const float getFront() const;

private:
	const fvec3 _position;

	const float _left;
	const float _right;
	const float _bottom;
	const float _top;
	const float _back;
	const float _front;
};