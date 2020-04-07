#include <WE3D/InputHandler.hpp>
#include <iostream>

void InputHandler::f_checkInput()
{
	p_timer.start("inputHandle");

	p_keysPressed.clear();
	p_mousePressed.clear();
	p_mouseWheelX = 0;
	p_mouseWheelY = 0;
	
	SDL_Event event;

	if (p_keysEnabled) 
	{
		while (SDL_PollEvent(&event)) // Check for any input
		{
			switch (event.type) 
			{	
				case SDL_QUIT: // X symbol in SDL window
				{
					p_keysDown.push_back(static_cast<Input>(SDL_QUIT));
					break;
				}

				case SDL_MOUSEWHEEL:
				{
					p_mouseWheelX = event.wheel.x;
					p_mouseWheelY = event.wheel.y;
					break;
				}

				case SDL_MOUSEBUTTONDOWN: // Continuing mouse press
				{
					auto button = static_cast<Input>(event.button.button);

					// Continuing mouse press
					if (!p_isInVector(p_mouseDown, button)) // If not in vector yet, add it
					{
						p_mouseDown.push_back(button);
					}

					// Toggled mouse press
					if (!p_isInVector(p_mouseToggled_mayNotPress, button)) // Mouse may be pressed
					{
						p_mouseToggled_mayNotPress.push_back(button); // Mouse may not be pressed next frame

						if (getMouseToggled(button)) // Make mouse toggle false
						{
							p_mouseToggled.erase(p_mouseToggled.begin() + p_getVectorIndex(p_mouseToggled, button));

						}
						else
						{
							p_mouseToggled.push_back(button); // Make mouse toggle true
						}
					}

					// Single short mouse press
					if (!p_isInVector(p_mousePressed_mayNotPress, button)) // Mouse may be pressed
					{
						p_mousePressed.push_back(button);
						p_mousePressed_mayNotPress.push_back(button);
					}

					break;
				}
			
				case SDL_MOUSEBUTTONUP: // Mouse may be pressed again
				{
					auto button = static_cast<Input>(event.button.button);

					p_mouseDown.erase(p_mouseDown.begin() + p_getVectorIndex(p_mouseDown, button));
					p_mouseToggled_mayNotPress.erase(p_mouseToggled_mayNotPress.begin() + p_getVectorIndex(p_mouseToggled_mayNotPress, button));
					p_mousePressed_mayNotPress.clear();
					break;
				}

				case SDL_KEYDOWN: // Continuing key press
				{
					auto key = static_cast<Input>(event.key.keysym.sym);

					if (!p_isInVector(p_keysDown, key)) // If not in vector yet, add it
					{
						p_keysDown.push_back(key);
					}

					// Toggled key press
					if (!p_isInVector(p_keysToggled_mayNotPress, key)) // Key may be pressed
					{
						p_keysToggled_mayNotPress.push_back(key); // Key may not be pressed next frame

						if (getKeyToggled(key)) // Make key toggle false
						{
							p_keysToggled.erase(p_keysToggled.begin() + p_getVectorIndex(p_keysToggled, key));
						}
						else
						{
							p_keysToggled.push_back(key); // Make key toggle true
						}
					}

					// Single short key press
					if (!p_isInVector(p_keysPressed_mayNotPress, key)) // Key may be pressed
					{
						p_keysPressed.push_back(key);
						p_keysPressed_mayNotPress.push_back(key);
					}
				
					break;
				}

				case SDL_KEYUP: // Keys may be pressed again
				{
					auto key = static_cast<Input>(event.key.keysym.sym);

					p_keysDown.erase(p_keysDown.begin() + p_getVectorIndex(p_keysDown, key));
					p_keysToggled_mayNotPress.erase(p_keysToggled_mayNotPress.begin() + p_getVectorIndex(p_keysToggled_mayNotPress, key));
					p_keysPressed_mayNotPress.clear();
					break;
				}
			}
		}
	}

	p_timer.stop();
}

InputHandler::InputHandler(Timer& timer) :
	p_timer(timer)
{

}

const bool InputHandler::getKeyDown(Input keyName)
{
	return p_isInVector(p_keysDown, keyName);
}

const bool InputHandler::getKeyToggled(Input keyName)
{
	return p_isInVector(p_keysToggled, keyName);
}

const bool InputHandler::getKeyPressed(Input keyName)
{
	return p_isInVector(p_keysPressed, keyName);
}

const bool InputHandler::getMouseDown(Input mouseButton)
{
	return p_isInVector(p_mouseDown, mouseButton);
}

const bool InputHandler::getMousePressed(Input mouseButton)
{
	return p_isInVector(p_mousePressed, mouseButton);
}

const bool InputHandler::getMouseToggled(Input mouseButton)
{
	return p_isInVector(p_mouseToggled, mouseButton);
}

const int InputHandler::getMouseWheelX()
{
	return p_mouseWheelX;
}

const int InputHandler::getMouseWheelY()
{
	return p_mouseWheelY;
}
