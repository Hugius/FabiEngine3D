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
	const int getMouseWheelX();
	const int getMouseWheelY();

	// Booleans
	const bool isLocked();
	const bool isKeyDown(InputType key);
	const bool isKeyPressed(InputType key);
	const bool isMouseDown(InputType button);
	const bool isMousePressed(InputType button);

private:
	// Integers
	inline unsigned int _getVectorIndex(vector<InputType>& list, InputType element)
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
	inline bool _isInVector(vector<InputType>& list, InputType element)
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