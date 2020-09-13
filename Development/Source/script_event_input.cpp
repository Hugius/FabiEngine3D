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

InputType ScriptEventInput::getInputType()
{
	return _inputType;
}

InputMethod ScriptEventInput::getInputMethod()
{
	return _inputMethod;
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
	_inputElement = ScriptEventInput::_inputStringMap.at(name);
}