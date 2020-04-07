#include "InputHandler.hpp"
#include <iostream>

void InputHandler::f_checkInput()
{
	_timer.start("inputHandle");

	_keysPressed.clear();
	_mousePressed.clear();
	_mouseWheelX = 0;
	_mouseWheelY = 0;
	
	SDL_Event event;

	if (_keysEnabled) 
	{
		while (SDL_PollEvent(&event)) // Check for any input
		{
			switch (event.type) 
			{	
				case SDL_QUIT: // X symbol in SDL window
				{
					_keysDown.push_back(static_cast<Input>(SDL_QUIT));
					break;
				}

				case SDL_MOUSEWHEEL:
				{
					_mouseWheelX = event.wheel.x;
					_mouseWheelY = event.wheel.y;
					break;
				}

				case SDL_MOUSEBUTTONDOWN: // Continuing mouse press
				{
					auto button = static_cast<Input>(event.button.button);

					// Continuing mouse press
					if (!_isInVector(_mouseDown, button)) // If not in vector yet, add it
					{
						_mouseDown.push_back(button);
					}

					// Toggled mouse press
					if (!_isInVector(_mouseToggled_mayNotPress, button)) // Mouse may be pressed
					{
						_mouseToggled_mayNotPress.push_back(button); // Mouse may not be pressed next frame

						if (getMouseToggled(button)) // Make mouse toggle false
						{
							_mouseToggled.erase(_mouseToggled.begin() + _getVectorIndex(_mouseToggled, button));

						}
						else
						{
							_mouseToggled.push_back(button); // Make mouse toggle true
						}
					}

					// Single short mouse press
					if (!_isInVector(_mousePressed_mayNotPress, button)) // Mouse may be pressed
					{
						_mousePressed.push_back(button);
						_mousePressed_mayNotPress.push_back(button);
					}

					break;
				}
			
				case SDL_MOUSEBUTTONUP: // Mouse may be pressed again
				{
					auto button = static_cast<Input>(event.button.button);

					_mouseDown.erase(_mouseDown.begin() + _getVectorIndex(_mouseDown, button));
					_mouseToggled_mayNotPress.erase(_mouseToggled_mayNotPress.begin() + _getVectorIndex(_mouseToggled_mayNotPress, button));
					_mousePressed_mayNotPress.clear();
					break;
				}

				case SDL_KEYDOWN: // Continuing key press
				{
					auto key = static_cast<Input>(event.key.keysym.sym);

					if (!_isInVector(_keysDown, key)) // If not in vector yet, add it
					{
						_keysDown.push_back(key);
					}

					// Toggled key press
					if (!_isInVector(_keysToggled_mayNotPress, key)) // Key may be pressed
					{
						_keysToggled_mayNotPress.push_back(key); // Key may not be pressed next frame

						if (getKeyToggled(key)) // Make key toggle false
						{
							_keysToggled.erase(_keysToggled.begin() + _getVectorIndex(_keysToggled, key));
						}
						else
						{
							_keysToggled.push_back(key); // Make key toggle true
						}
					}

					// Single short key press
					if (!_isInVector(_keysPressed_mayNotPress, key)) // Key may be pressed
					{
						_keysPressed.push_back(key);
						_keysPressed_mayNotPress.push_back(key);
					}
				
					break;
				}

				case SDL_KEYUP: // Keys may be pressed again
				{
					auto key = static_cast<Input>(event.key.keysym.sym);

					_keysDown.erase(_keysDown.begin() + _getVectorIndex(_keysDown, key));
					_keysToggled_mayNotPress.erase(_keysToggled_mayNotPress.begin() + _getVectorIndex(_keysToggled_mayNotPress, key));
					_keysPressed_mayNotPress.clear();
					break;
				}
			}
		}
	}

	_timer.stop();
}

InputHandler::InputHandler(Timer& timer) :
	_timer(timer)
{

}

const bool InputHandler::getKeyDown(Input keyName)
{
	return _isInVector(_keysDown, keyName);
}

const bool InputHandler::getKeyToggled(Input keyName)
{
	return _isInVector(_keysToggled, keyName);
}

const bool InputHandler::getKeyPressed(Input keyName)
{
	return _isInVector(_keysPressed, keyName);
}

const bool InputHandler::getMouseDown(Input mouseButton)
{
	return _isInVector(_mouseDown, mouseButton);
}

const bool InputHandler::getMousePressed(Input mouseButton)
{
	return _isInVector(_mousePressed, mouseButton);
}

const bool InputHandler::getMouseToggled(Input mouseButton)
{
	return _isInVector(_mouseToggled, mouseButton);
}

const int InputHandler::getMouseWheelX()
{
	return _mouseWheelX;
}

const int InputHandler::getMouseWheelY()
{
	return _mouseWheelY;
}
