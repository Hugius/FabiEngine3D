#include "script_event_input.hpp"

bool ScriptEventInput::isTriggered()
{
	// Determine input type & method
	if (_inputMethod == InputEventMethod::DOWN)
	{
		if (_inputType == InputEventType::KEYBOARD)
		{
			return _fe3d.input_getKeyDown(_inputElement);
		}
		else if (_inputType == InputEventType::MOUSE)
		{
			return _fe3d.input_getMouseDown(_inputElement);
		}
	}
	else if (_inputMethod == InputEventMethod::PRESSED)
	{
		if (_inputType == InputEventType::KEYBOARD)
		{
			return _fe3d.input_getKeyPressed(_inputElement);
		}
		else if (_inputType == InputEventType::MOUSE)
		{
			return _fe3d.input_getMousePressed(_inputElement);
		}
	}
	else if (_inputMethod == InputEventMethod::TOGGLED)
	{
		if (_inputType == InputEventType::KEYBOARD)
		{
			return _fe3d.input_getKeyToggled(_inputElement);
		}
		else if (_inputType == InputEventType::MOUSE)
		{
			return _fe3d.input_getMouseToggled(_inputElement);
		}
	}
	else if (_inputType == InputEventType::MOUSE)
	{
		if (_inputMouseType == InputEventMouseType::SCROLL_UP)
		{
			return _fe3d.input_getMouseWheelY() > 0;
		}
		else if (_inputMouseType == InputEventMouseType::SCROLL_DOWN)
		{
			return _fe3d.input_getMouseWheelY() < 0;
		}
	}

	return false;
}

void ScriptEventInput::setInputType(InputEventType type)
{
	_inputType = type;
}

void ScriptEventInput::setMouseType(InputEventMouseType type)
{
	_inputMouseType = type;
}

void ScriptEventInput::setInputMethod(InputEventMethod method)
{
	_inputMethod = method;
}

void ScriptEventInput::setInputElement(string name)
{
	if (_inputType == InputEventType::KEYBOARD)
	{
		_inputElement = ScriptEventInput::_keyInputStringMap.at(name);
	}
	else if(_inputType == InputEventType::MOUSE)
	{
		_inputElement = ScriptEventInput::_mouseInputStringMap.at(name);
	}
}

void ScriptEventInput::setInputElement(Input element)
{
	_inputElement = element;
}

InputEventType ScriptEventInput::getInputType()
{
	return _inputType;
}

InputEventMouseType ScriptEventInput::getMouseType()
{
	return _inputMouseType;
}

InputEventMethod ScriptEventInput::getInputMethod()
{
	return _inputMethod;
}

Input ScriptEventInput::getInputElement()
{
	return _inputElement;
}

int ScriptEventInput::getInputElementIndex()
{
	int index = 0;

	if (_inputType == InputEventType::KEYBOARD)
	{
		for (auto& [key, val] : _keyInputStringMap)
		{
			if (val == _inputElement)
			{
				return index;
			}
			index++;
		}
	}
	else if (_inputType == InputEventType::MOUSE)
	{
		for (auto& [key, val] : _mouseInputStringMap)
		{
			if (val == _inputElement)
			{
				return index;
			}
			index++;
		}
	}

	return -1;
}