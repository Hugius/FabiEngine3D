#pragma once

#include "input_type.hpp"
#include "logger.hpp"

#include <vector>

using std::vector;

class InputHandler final
{
public:
	void update();
	void clearKeyToggles();
	void clearMouseToggles();
	void setLocked(bool locked);
	void setKeyTogglingLocked(bool locked);
	void setMouseTogglingLocked(bool locked);

	const bool isKeyDown(InputType keyName);
	const bool isKeyPressed(InputType keyName);
	const bool isKeyToggled(InputType keyName);
	const bool isMouseDown(InputType mouseButton);
	const bool isMousePressed(InputType mouseButton);
	const bool isMouseToggled(InputType mouseButton);

	const int  getMouseWheelX();
	const int  getMouseWheelY();

private:
	// Keys
	vector<InputType> _keysDown;
	vector<InputType> _keysPressed;
	vector<InputType> _keysPressed_mayNotPress;
	vector<InputType> _keysToggled;
	vector<InputType> _keysToggled_mayNotPress;

	// Mouse buttons
	vector<InputType> _mouseDown;
	vector<InputType> _mousePressed;
	vector<InputType> _mousePressed_mayNotPress;
	vector<InputType> _mouseToggled;
	vector<InputType> _mouseToggled_mayNotPress;

	// Mouse scrolling wheel
	int _mouseWheelX = 0;
	int _mouseWheelY = 0;

	// Miscellaneous
	bool _everythingLocked = false;
	bool _keyTogglingLocked = false;
	bool _mouseTogglingLocked = false;

	// Extra functions
	inline unsigned int _getVectorIndex(vector<InputType>& list, InputType element)
	{
		auto it = std::find(list.begin(), list.end(), element);

		if (it == list.end()) // Not found
		{
			Logger::throwError("Failed to get input " + std::to_string(static_cast<int>(element)) + " index from vector!");
		}
		else // Found
		{
			return static_cast<unsigned int>(std::distance(list.begin(), it));
		}
	}
	inline bool _isInVector(vector<InputType>& list, InputType element)
	{
		return std::find(list.begin(), list.end(), element) != list.end();
	}
};