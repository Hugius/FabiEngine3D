#pragma once

#include "input_types.hpp"
#include "logger.hpp"
#include "Timer.hpp"

#include <SDL\\SDL.h>
#include <vector>

using std::vector;

class InputHandler final
{
	friend class CoreEngine;
public:
	InputHandler(Timer& timer);
	~InputHandler() = default;

	void setLocked(bool locked);
	void setKeyTogglingLocked(bool locked);
	void setMouseTogglingLocked(bool locked);
	const bool getKeyDown(Input keyName);
	const bool getKeyPressed(Input keyName);
	const bool getKeyToggled(Input keyName);
	const bool getMouseDown(Input mouseButton);
	const bool getMousePressed(Input mouseButton);
	const bool getMouseToggled(Input mouseButton);
	const int  getMouseWheelX();
	const int  getMouseWheelY();

private:
	void f_checkInput();

	Timer& _timer;

	// Keys
	vector<Input> _keysDown;
	vector<Input> _keysPressed;
	vector<Input> _keysPressed_mayNotPress;
	vector<Input> _keysToggled;
	vector<Input> _keysToggled_mayNotPress;
	
	bool _everythingLocked = false;
	bool _keyTogglingLocked = false;
	bool _mouseTogglingLocked = false;

	// Mouse buttons
	vector<Input> _mouseDown;
	vector<Input> _mousePressed;
	vector<Input> _mousePressed_mayNotPress;
	vector<Input> _mouseToggled;
	vector<Input> _mouseToggled_mayNotPress;

	// Mouse scrolling wheel
	int _mouseWheelX = 0;
	int _mouseWheelY = 0;

	// Extra functions
	inline int _getVectorIndex(vector<Input>& list, Input element)
	{
		auto it = std::find(list.begin(), list.end(), element);

		if (it == list.end()) // Not found
		{
			Logger::getInst().throwError("Failed to get input " + std::to_string(static_cast<int>(element)) + " index from vector!");
		}
		else // Found
		{
			return std::distance(list.begin(), it);
		}
	}

	inline bool _isInVector(vector<Input>& list, Input element)
	{
		return std::find(list.begin(), list.end(), element) != list.end();
	}
};