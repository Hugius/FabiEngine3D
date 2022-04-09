#include "input_handler.hpp"

#include <windows.h>
#include <SDL.h>

void InputHandler::update()
{
	_pressedKeyboardKeys.clear();
	_pressedMouseButtons.clear();
	_horizontalMouseWheel = 0;
	_verticalMouseWheel = 0;

	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
	}

	for(const auto button : _mouseButtons)
	{
		if(GetKeyState(static_cast<int>(button)) & 0x1000000000000000)
		{
			if(!isMouseButtonHeld(button))
			{
				_heldMouseButtons.push_back(button);
				_pressedMouseButtons.push_back(button);
			}
		}
		else
		{
			for(unsigned int index = 0; index < static_cast<unsigned int>(_heldMouseButtons.size()); index++)
			{
				if(button == _heldMouseButtons[index])
				{
					_heldMouseButtons.erase(_heldMouseButtons.begin() + index);

					break;
				}
			}
		}
	}

	for(const auto key : _keyboardKeys)
	{
		if(GetKeyState(static_cast<int>(key)) & 0x1000000000000000)
		{
			if(!isKeyboardKeyHeld(key))
			{
				_heldKeyboardKeys.push_back(key);
				_pressedKeyboardKeys.push_back(key);
			}
		}
		else
		{
			for(unsigned int index = 0; index < static_cast<unsigned int>(_heldKeyboardKeys.size()); index++)
			{
				if(key == _heldKeyboardKeys[index])
				{
					_heldKeyboardKeys.erase(_heldKeyboardKeys.begin() + index);

					break;
				}
			}
		}
	}
}

const bool InputHandler::isKeyboardKeyHeld(InputType key) const
{
	return (find(_heldKeyboardKeys.begin(), _heldKeyboardKeys.end(), key) != _heldKeyboardKeys.end());
}

const bool InputHandler::isKeyboardKeyPressed(InputType key) const
{
	return (find(_pressedKeyboardKeys.begin(), _pressedKeyboardKeys.end(), key) != _pressedKeyboardKeys.end());
}

const bool InputHandler::isMouseButtonHeld(InputType button) const
{
	return (find(_heldMouseButtons.begin(), _heldMouseButtons.end(), button) != _heldMouseButtons.end());
}

const bool InputHandler::isMouseButtonPressed(InputType button) const
{
	return (find(_pressedMouseButtons.begin(), _pressedMouseButtons.end(), button) != _pressedMouseButtons.end());
}

const int InputHandler::getHorizontalMouseWheel() const
{
	return _horizontalMouseWheel;
}

const int InputHandler::getVerticalMouseWheel() const
{
	return _verticalMouseWheel;
}