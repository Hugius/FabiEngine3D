#include "input_handler.hpp"

#include <shlobj_core.h>

void InputHandler::update()
{
	_scrolledMouseWheels.clear();
	_pressedMouseButtons.clear();
	_pressedKeyboardKeyTypes.clear();
	_toggledMouseButtons.clear();
	_toggledKeyboardKeyTypes.clear();

	for(const auto & wheel : _mouseWheelEvents)
	{
		_scrolledMouseWheels.push_back(wheel);
	}

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
			_heldKeyboardKeyTypes.push_back(key);
			_pressedKeyboardKeyTypes.push_back(key);
		}
	}

	for(const auto & button : _mouseUpEvents)
	{
		_heldMouseButtons.erase(find(_heldMouseButtons.begin(), _heldMouseButtons.end(), button));
	}

	for(const auto & key : _keyboardUpEvents)
	{
		_heldKeyboardKeyTypes.erase(find(_heldKeyboardKeyTypes.begin(), _heldKeyboardKeyTypes.end(), key));
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
			_toggledKeyboardKeyTypes.push_back(key);
		}
	}

	_mouseWheelEvents.clear();
	_mouseDownEvents.clear();
	_mouseUpEvents.clear();
	_keyboardDownEvents.clear();
	_keyboardUpEvents.clear();
}

void InputHandler::sendMouseWheelEvent(MouseWheelType wheel)
{
	_mouseWheelEvents.push_back(wheel);
}

void InputHandler::sendMouseDownEvent(MouseButtonType button)
{
	_mouseDownEvents.push_back(button);
}

void InputHandler::sendMouseUpEvent(MouseButtonType button)
{
	_mouseUpEvents.push_back(button);
}

void InputHandler::sendKeyboardDownEvent(KeyboardKeyType key)
{
	_keyboardDownEvents.push_back(key);
}

void InputHandler::sendKeyboardUpEvent(KeyboardKeyType key)
{
	_keyboardUpEvents.push_back(key);
}

const bool InputHandler::isKeyboardHeld(KeyboardKeyType key) const
{
	return (find(_heldKeyboardKeyTypes.begin(), _heldKeyboardKeyTypes.end(), key) != _heldKeyboardKeyTypes.end());
}

const bool InputHandler::isKeyboardPressed(KeyboardKeyType key) const
{
	return (find(_pressedKeyboardKeyTypes.begin(), _pressedKeyboardKeyTypes.end(), key) != _pressedKeyboardKeyTypes.end());
}

const bool InputHandler::isKeyboardToggled(KeyboardKeyType key) const
{
	return (find(_toggledKeyboardKeyTypes.begin(), _toggledKeyboardKeyTypes.end(), key) != _toggledKeyboardKeyTypes.end());
}

const bool InputHandler::isMouseScrolled(MouseWheelType wheel) const
{
	return (find(_scrolledMouseWheels.begin(), _scrolledMouseWheels.end(), wheel) != _scrolledMouseWheels.end());
}

const bool InputHandler::isMouseHeld(MouseButtonType button) const
{
	return (find(_heldMouseButtons.begin(), _heldMouseButtons.end(), button) != _heldMouseButtons.end());
}

const bool InputHandler::isMousePressed(MouseButtonType button) const
{
	return (find(_pressedMouseButtons.begin(), _pressedMouseButtons.end(), button) != _pressedMouseButtons.end());
}

const bool InputHandler::isMouseToggled(MouseButtonType button) const
{
	return (find(_toggledMouseButtons.begin(), _toggledMouseButtons.end(), button) != _toggledMouseButtons.end());
}