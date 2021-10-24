#pragma once

class Box final
{
public:
	Box(float left, float right, float bottom, float top, float front, float back);

	const float getLeft() const;
	const float getRight() const;
	const float getBottom() const;
	const float getTop() const;
	const float getFront() const;
	const float getBack() const;

private:
	float _left;
	float _right;
	float _bottom;
	float _top;
	float _front;
	float _back;
};