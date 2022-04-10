#include "input_handler.hpp"

#include <windows.h>
#include <SDL.h>

void InputHandler::update()
{
	_pressedMouseButtons.clear();
	_pressedKeyboardKeys.clear();
	_toggledMouseButtons.clear();
	_toggledKeyboardKeys.clear();
	_horizontalMouseWheel = 0;
	_verticalMouseWheel = 0;

	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
	}

	for(const auto button : _buttons)
	{
		if(GetKeyState(static_cast<int>(button)) & (1 << 15))
		{
			if(!isMouseHeld(button))
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

		if(GetKeyState(static_cast<int>(button)) & 1)
		{
			_toggledMouseButtons.push_back(button);
		}
	}

	for(const auto key : _keys)
	{
		if(GetKeyState(static_cast<int>(key)) & (1 << 15))
		{
			if(!isKeyboardHeld(key))
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

		if(GetKeyState(static_cast<int>(key)) & 1)
		{
			_toggledKeyboardKeys.push_back(key);
		}
	}
}

const bool InputHandler::isKeyboardHeld(KeyType key) const
{
	return (find(_heldKeyboardKeys.begin(), _heldKeyboardKeys.end(), key) != _heldKeyboardKeys.end());
}

const bool InputHandler::isKeyboardPressed(KeyType key) const
{
	return (find(_pressedKeyboardKeys.begin(), _pressedKeyboardKeys.end(), key) != _pressedKeyboardKeys.end());
}

const bool InputHandler::isKeyboardToggled(KeyType key) const
{
	return (find(_toggledKeyboardKeys.begin(), _toggledKeyboardKeys.end(), key) != _toggledKeyboardKeys.end());
}

const bool InputHandler::isMouseHeld(ButtonType button) const
{
	return (find(_heldMouseButtons.begin(), _heldMouseButtons.end(), button) != _heldMouseButtons.end());
}

const bool InputHandler::isMousePressed(ButtonType button) const
{
	return (find(_pressedMouseButtons.begin(), _pressedMouseButtons.end(), button) != _pressedMouseButtons.end());
}

const bool InputHandler::isMouseToggled(ButtonType button) const
{
	return (find(_toggledMouseButtons.begin(), _toggledMouseButtons.end(), button) != _toggledMouseButtons.end());
}

const int InputHandler::getHorizontalMouseWheel() const
{
	return _horizontalMouseWheel;
}

const int InputHandler::getVerticalMouseWheel() const
{
	return _verticalMouseWheel;
}