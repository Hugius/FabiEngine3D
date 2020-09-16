#include "script_event_input.hpp"

bool ScriptEventInput::isTriggered()
{
	// Determine input type & method
	if (_inputMethod == InputMethod::DOWN)
	{
		if (_inputType == InputType::KEYBOARD)
		{
			return _fe3d.input_getKeyDown(_inputElement);
		}
		else if (_inputType == InputType::MOUSE)
		{
			return _fe3d.input_getMouseDown(_inputElement);
		}
	}
	else if (_inputMethod == InputMethod::PRESSED)
	{
		if (_inputType == InputType::KEYBOARD)
		{
			return _fe3d.input_getKeyPressed(_inputElement);
		}
		else if (_inputType == InputType::MOUSE)
		{
			return _fe3d.input_getMousePressed(_inputElement);
		}
	}
	else if (_inputMethod == InputMethod::TOGGLED)
	{
		if (_inputType == InputType::KEYBOARD)
		{
			return _fe3d.input_getKeyToggled(_inputElement);
		}
		else if (_inputType == InputType::MOUSE)
		{
			return _fe3d.input_getMouseToggled(_inputElement);
		}
	}

	return false;
}

void ScriptEventInput::setInputType(InputType type)
{
	_inputType = type;
}

void ScriptEventInput::setInputMethod(InputMethod method)
{
	_inputMethod = method;
}

void ScriptEventInput::setInputElement(string name)
{
	if (_inputType == InputType::KEYBOARD)
	{
		_inputElement = ScriptEventInput::_keyInputStringMap.at(name);
	}
	else if(_inputType == InputType::MOUSE)
	{
		_inputElement = ScriptEventInput::_keyInputStringMap.at(name);
	}
}

void ScriptEventInput::setInputElement(Input element)
{
	_inputElement = element;
}

InputType ScriptEventInput::getInputType()
{
	return _inputType;
}

InputMethod ScriptEventInput::getInputMethod()
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

	if (_inputType == InputType::KEYBOARD)
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
	else if (_inputType == InputType::MOUSE)
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