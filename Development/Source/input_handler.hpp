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

	const bool isLocked();
	const bool isKeyDown(InputType key);
	const bool isKeyPressed(InputType key);
	const bool isMouseDown(InputType button);
	const bool isMousePressed(InputType button);

	const int getMouseWheelX();
	const int getMouseWheelY();

private:
	// Keys
	vector<InputType> _keysDown;
	vector<InputType> _keysPressed;
	vector<InputType> _keysPressed_mayNotPress;

	// Mouse buttons
	vector<InputType> _mouseDown;
	vector<InputType> _mousePressed;
	vector<InputType> _mousePressed_mayNotPress;

	// Mouse scrolling wheel
	int _mouseWheelX = 0;
	int _mouseWheelY = 0;

	// Miscellaneous
	bool _isLocked = false;

	// Extra functions
	inline unsigned int _getVectorIndex(vector<InputType>& list, InputType element)
	{
		auto it = find(list.begin(), list.end(), element);

		if (it == list.end()) // Not found
		{
			Logger::throwFatalError("InputHandler::_getVectorIndex");
		}
		else // Found
		{
			return static_cast<unsigned int>(distance(list.begin(), it));
		}
	}
	inline bool _isInVector(vector<InputType>& list, InputType element)
	{
		return find(list.begin(), list.end(), element) != list.end();
	}
};