#pragma once

#include "input_type.hpp"
#include "logger.hpp"

#include <vector>

using std::to_string;
using std::vector;

class InputHandler final
{
public:
	// Voids
	void update();
	void setLocked(bool locked);

	// Integers
	const int getMouseWheelX() const;
	const int getMouseWheelY() const;

	// Booleans
	const bool isLocked() const;
	const bool isKeyDown(InputType key) const;
	const bool isKeyPressed(InputType key) const;
	const bool isMouseDown(InputType button) const;
	const bool isMousePressed(InputType button) const;

private:
	// Integers
	inline const unsigned int _getVectorIndex(const vector<InputType>& list, InputType element) const
	{
		auto it = find(list.begin(), list.end(), element);

		if(it == list.end()) // Not found
		{
			Logger::throwError("InputHandler::_getVectorIndex");
		}
		else // Found
		{
			return static_cast<unsigned int>(distance(list.begin(), it));
		}
	}

	// Booleans
	inline const bool _isInVector(const vector<InputType>& list, InputType element) const
	{
		return find(list.begin(), list.end(), element) != list.end();
	}

	// Integers
	int _mouseWheelX = 0;
	int _mouseWheelY = 0;

	// Booleans
	bool _isLocked = false;

	// Miscellaneous
	vector<InputType> _keysDown;
	vector<InputType> _keysPressed;
	vector<InputType> _keysPressed_mayNotPress;
	vector<InputType> _mouseDown;
	vector<InputType> _mousePressed;
	vector<InputType> _mousePressed_mayNotPress;
};