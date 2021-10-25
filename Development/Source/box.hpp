#pragma once

class Box final
{
public:
	Box(float left, float right, float bottom, float top, float back, float front);

	const float getLeft() const;
	const float getRight() const;
	const float getBottom() const;
	const float getTop() const;
	const float getBack() const;
	const float getFront() const;

private:
	float _left;
	float _right;
	float _bottom;
	float _top;
	float _back;
	float _front;
};