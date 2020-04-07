#pragma once

#include <SDL/SDL.h>
#include <vector>

using std::vector;

#include <WE3D/InputTypes.hpp>
#include "Logger.hpp"
#include "Timer.hpp"

class InputHandler final
{
	friend class CoreEngine;
public:
	InputHandler(Timer& timer);
	~InputHandler() = default;

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

	Timer& p_timer;

	// Keys
	vector<Input> p_keysDown;
	vector<Input> p_keysPressed;
	vector<Input> p_keysPressed_mayNotPress;
	vector<Input> p_keysToggled;
	vector<Input> p_keysToggled_mayNotPress;
	
	bool p_keysEnabled = true;

	// Mouse buttons
	vector<Input> p_mouseDown;
	vector<Input> p_mousePressed;
	vector<Input> p_mousePressed_mayNotPress;
	vector<Input> p_mouseToggled;
	vector<Input> p_mouseToggled_mayNotPress;

	// Mouse scrolling wheel
	int p_mouseWheelX = 0;
	int p_mouseWheelY = 0;

	// Extra functions
	inline int p_getVectorIndex(vector<Input>& list, Input element)
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

	inline bool p_isInVector(vector<Input>& list, Input element)
	{
		return std::find(list.begin(), list.end(), element) != list.end();
	}
};