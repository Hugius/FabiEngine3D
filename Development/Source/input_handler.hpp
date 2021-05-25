#pragma once

#include "input_type.hpp"
#include "logger.hpp"

#include <SDL\\SDL.h>
#include <vector>

using std::vector;

class InputHandler final
{
	friend class CoreEngine;
public:
	void clearKeyToggles();
	void clearMouseToggles();
	void setLocked(bool locked);
	void setKeyTogglingLocked(bool locked);
	void setMouseTogglingLocked(bool locked);
	const bool getKeyDown(InputType keyName);
	const bool getKeyPressed(InputType keyName);
	const bool getKeyToggled(InputType keyName);
	const bool getMouseDown(InputType mouseButton);
	const bool getMousePressed(InputType mouseButton);
	const bool getMouseToggled(InputType mouseButton);
	const int  getMouseWheelX();
	const int  getMouseWheelY();

private:
	void f_checkInput();

	// Keys
	vector<InputType> _keysDown;
	vector<InputType> _keysPressed;
	vector<InputType> _keysPressed_mayNotPress;
	vector<InputType> _keysToggled;
	vector<InputType> _keysToggled_mayNotPress;
	
	bool _everythingLocked = false;
	bool _keyTogglingLocked = false;
	bool _mouseTogglingLocked = false;

	// Mouse buttons
	vector<InputType> _mouseDown;
	vector<InputType> _mousePressed;
	vector<InputType> _mousePressed_mayNotPress;
	vector<InputType> _mouseToggled;
	vector<InputType> _mouseToggled_mayNotPress;

	// Mouse scrolling wheel
	int _mouseWheelX = 0;
	int _mouseWheelY = 0;

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