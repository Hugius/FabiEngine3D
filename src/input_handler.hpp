#pragma once

#include "input_type.hpp"
#include "logger.hpp"

#include <vector>

using std::to_string;
using std::vector;

class InputHandler final
{
public:
	void update();
	void setLocked(bool locked);

	const int getMouseWheelX() const;
	const int getMouseWheelY() const;

	const bool isLocked() const;
	const bool isKeyDown(InputType key) const;
	const bool isKeyPressed(InputType key) const;
	const bool isMouseDown(InputType button) const;
	const bool isMousePressed(InputType button) const;

private:
	inline const unsigned int _getVectorIndex(const vector<InputType>& list, InputType element) const
	{
		auto iterator = find(list.begin(), list.end(), element);

		if(iterator == list.end())
		{
			abort();
		}
		else
		{
			return static_cast<unsigned int>(distance(list.begin(), iterator));
		}
	}

	inline const bool _isInVector(const vector<InputType>& list, InputType element) const
	{
		return find(list.begin(), list.end(), element) != list.end();
	}

	int _mouseWheelX = 0;
	int _mouseWheelY = 0;

	bool _isLocked = false;

	vector<InputType> _keysDown;
	vector<InputType> _keysPressed;
	vector<InputType> _keysPressed_mayNotPress;
	vector<InputType> _mouseDown;
	vector<InputType> _mousePressed;
	vector<InputType> _mousePressed_mayNotPress;
};