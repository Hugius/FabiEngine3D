#include "input_handler.hpp"

void InputHandler::f_checkInput()
{
	_keysPressed.clear();
	_mousePressed.clear();
	_mouseWheelX = 0;
	_mouseWheelY = 0;
	
	SDL_Event event;

	if (!_everythingLocked) 
	{
		while (SDL_PollEvent(&event)) // Check for any input
		{
			switch (event.type) 
			{	
				case SDL_QUIT: // X symbol in SDL window
				{
					_keysDown.push_back(static_cast<InputType>(SDL_QUIT));
					break;
				}

				case SDL_MOUSEWHEEL:
				{
					_mouseWheelX = event.wheel.x;
					_mouseWheelY = event.wheel.y;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					auto button = static_cast<InputType>(event.button.button);

					// Continuing mouse press
					if (!_isInVector(_mouseDown, button)) // If not in vector yet, add it
					{
						_mouseDown.push_back(button);
					}

					// Toggled mouse press
					if (!_mouseTogglingLocked)
					{
						if (!_isInVector(_mouseToggled_mayNotPress, button)) // Mouse may be pressed
						{
							_mouseToggled_mayNotPress.push_back(button); // Mouse may not be pressed next frame

							if (isMouseToggled(button)) // Make mouse toggle false
							{
								if (!_mouseToggled.empty())
								{
									if (std::find(_mouseToggled.begin(), _mouseToggled.end(), button) != _mouseToggled.end())
									{
										_mouseToggled.erase(_mouseToggled.begin() + _getVectorIndex(_mouseToggled, button));
									}
								}

							}
							else
							{
								_mouseToggled.push_back(button); // Make mouse toggle true
							}
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
			
				case SDL_MOUSEBUTTONUP:
				{
					auto button = static_cast<InputType>(event.button.button);

					// Continuing mouse press
					if (!_mouseDown.empty())
					{
						_mouseDown.erase(_mouseDown.begin() + _getVectorIndex(_mouseDown, button));
					}

					// Toggled mouse press
					if (!_mouseTogglingLocked)
					{
						if (!_mouseToggled_mayNotPress.empty())
						{
							if (std::find(_mouseToggled_mayNotPress.begin(), _mouseToggled_mayNotPress.end(), button) != _mouseToggled_mayNotPress.end())
							{
								_mouseToggled_mayNotPress.erase(_mouseToggled_mayNotPress.begin() + _getVectorIndex(_mouseToggled_mayNotPress, button));
							}
						}
					}

					// Single short mouse press
					_mousePressed_mayNotPress.clear();

					break;
				}

				case SDL_KEYDOWN:
				{
					auto key = static_cast<InputType>(event.key.keysym.sym);

					// Continuing key press
					if (!_isInVector(_keysDown, key))
					{
						_keysDown.push_back(key);
					}

					// Toggled key press
					if (!_keyTogglingLocked)
					{
						if (!_isInVector(_keysToggled_mayNotPress, key)) // Key may be pressed
						{
							_keysToggled_mayNotPress.push_back(key); // Key may not be pressed next frame

							if (isKeyToggled(key)) // Make key toggle false
							{
								if (!_keysToggled.empty())
								{
									if (std::find(_keysToggled.begin(), _keysToggled.end(), key) != _keysToggled.end())
									{
										_keysToggled.erase(_keysToggled.begin() + _getVectorIndex(_keysToggled, key));
									}
								}
							}
							else
							{
								_keysToggled.push_back(key); // Make key toggle true
							}
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

				case SDL_KEYUP:
				{
					auto key = static_cast<InputType>(event.key.keysym.sym);

					// Continuing key press
					if (!_keysDown.empty())
					{
						_keysDown.erase(_keysDown.begin() + _getVectorIndex(_keysDown, key));
					}

					// Toggled key press
					if (!_keyTogglingLocked)
					{
						if (!_keysToggled_mayNotPress.empty())
						{
							if (std::find(_keysToggled_mayNotPress.begin(), _keysToggled_mayNotPress.end(), key) != _keysToggled_mayNotPress.end())
							{
								_keysToggled_mayNotPress.erase(_keysToggled_mayNotPress.begin() + _getVectorIndex(_keysToggled_mayNotPress, key));
							}
						}
					}

					// Single short key press
					_keysPressed_mayNotPress.clear();

					break;
				}
			}
		}
	}
}

void InputHandler::clearKeyToggles()
{
	_keysToggled.clear();
	_keysToggled_mayNotPress.clear();
}

void InputHandler::clearMouseToggles()
{
	_mouseToggled.clear();
	_mouseToggled_mayNotPress.clear();
}

void InputHandler::setLocked(bool locked)
{
	_everythingLocked = locked;
}

void InputHandler::setKeyTogglingLocked(bool locked)
{
	_keyTogglingLocked = locked;
}

void InputHandler::setMouseTogglingLocked(bool locked)
{
	_mouseTogglingLocked = locked;
}

const bool InputHandler::isKeyDown(InputType keyName)
{
	return _isInVector(_keysDown, keyName);
}

const bool InputHandler::isKeyToggled(InputType keyName)
{
	return _isInVector(_keysToggled, keyName);
}

const bool InputHandler::isKeyPressed(InputType keyName)
{
	return _isInVector(_keysPressed, keyName);
}

const bool InputHandler::isMouseDown(InputType mouseButton)
{
	return _isInVector(_mouseDown, mouseButton);
}

const bool InputHandler::isMousePressed(InputType mouseButton)
{
	return _isInVector(_mousePressed, mouseButton);
}

const bool InputHandler::isMouseToggled(InputType mouseButton)
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
