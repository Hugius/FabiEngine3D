#pragma once

#include "mathematics.hpp"

class Box final
{
public:
	Box(fvec3 position, float left, float right, float bottom, float top, float back, float front);
	Box(float left, float right, float bottom, float top, float back, float front);

	// Vectors
	const fvec3 getPosition() const;

	// Decimals
	const float getLeft() const;
	const float getRight() const;
	const float getBottom() const;
	const float getTop() const;
	const float getBack() const;
	const float getFront() const;

private:
	// Vectors
	fvec3 _position;

	// Decimals
	float _left;
	float _right;
	float _bottom;
	float _top;
	float _back;
	float _front;
};