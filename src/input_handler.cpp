#include "input_handler.hpp"

#include <shlobj_core.h>

void InputHandler::update()
{
	_pressedMouseButtons.clear();
	_pressedKeyboardKeys.clear();
	_toggledMouseButtons.clear();
	_toggledKeyboardKeys.clear();

	for(const auto & button : _mouseDownEvents)
	{
		if(!isMouseHeld(button))
		{
			_heldMouseButtons.push_back(button);
			_pressedMouseButtons.push_back(button);
		}
	}

	for(const auto & key : _keyboardDownEvents)
	{
		if(!isKeyboardHeld(key))
		{
			_heldKeyboardKeys.push_back(key);
			_pressedKeyboardKeys.push_back(key);
		}
	}

	for(const auto & button : _mouseUpEvents)
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

	for(const auto & key : _keyboardUpEvents)
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

	for(const auto & button : _mouseButtons)
	{
		if(GetKeyState(static_cast<int>(button)) & 1)
		{
			_toggledMouseButtons.push_back(button);
		}
	}

	for(const auto & key : _keyboardKeys)
	{
		if(GetKeyState(static_cast<int>(key)) & 1)
		{
			_toggledKeyboardKeys.push_back(key);
		}
	}

	_mouseDownEvents.clear();
	_mouseUpEvents.clear();
	_keyboardDownEvents.clear();
	_keyboardUpEvents.clear();
}

void InputHandler::sendMouseDownEvent(ButtonType button)
{
	_mouseDownEvents.push_back(button);
}

void InputHandler::sendMouseUpEvent(ButtonType button)
{
	_mouseUpEvents.push_back(button);
}

void InputHandler::sendKeyboardDownEvent(KeyType key)
{
	_keyboardDownEvents.push_back(key);
}

void InputHandler::sendKeyboardUpEvent(KeyType key)
{
	_keyboardUpEvents.push_back(key);
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

const int InputHandler::getVerticalMouseWheel() const
{
	return _verticalMouseWheel;
}