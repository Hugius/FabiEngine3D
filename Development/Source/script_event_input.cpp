#include "script_event_input.hpp"

ScriptEventInput::ScriptEventInput(FabiEngine3D& fe3d, InputType inputType, InputTypeMethod inputTypeMethod, string inputElementName) :
	ScriptEvent(fe3d, ScriptEventType::INPUT_EVENT),
	_inputType(inputType),
	_inputTypeMethod(inputTypeMethod)
{
	_inputElement = InputStringConverter::getInst().getMap()[inputElementName];
}

bool ScriptEventInput::isTriggered()
{
	// Determine input type & method
	if (_inputTypeMethod == InputTypeMethod::DOWN)
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
	else if (_inputTypeMethod == InputTypeMethod::PRESSED)
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
	else if (_inputTypeMethod == InputTypeMethod::TOGGLED)
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
}

ScriptEventInput::InputStringConverter::InputStringConverter()
{
	_inputStringMap.insert(std::make_pair("KEY_A", Input::KEY_A));
	_inputStringMap.insert(std::make_pair("KEY_B", Input::KEY_B));
	_inputStringMap.insert(std::make_pair("KEY_C", Input::KEY_C));
	_inputStringMap.insert(std::make_pair("KEY_D", Input::KEY_D));
	_inputStringMap.insert(std::make_pair("KEY_E", Input::KEY_E));
	_inputStringMap.insert(std::make_pair("KEY_F", Input::KEY_F));
	_inputStringMap.insert(std::make_pair("KEY_G", Input::KEY_G));
	_inputStringMap.insert(std::make_pair("KEY_H", Input::KEY_H));
	_inputStringMap.insert(std::make_pair("KEY_I", Input::KEY_I));
	_inputStringMap.insert(std::make_pair("KEY_J", Input::KEY_J));
	_inputStringMap.insert(std::make_pair("KEY_K", Input::KEY_K));
	_inputStringMap.insert(std::make_pair("KEY_L", Input::KEY_L));
	_inputStringMap.insert(std::make_pair("KEY_M", Input::KEY_M));
	_inputStringMap.insert(std::make_pair("KEY_N", Input::KEY_N));
	_inputStringMap.insert(std::make_pair("KEY_O", Input::KEY_O));
	_inputStringMap.insert(std::make_pair("KEY_P", Input::KEY_P));
	_inputStringMap.insert(std::make_pair("KEY_A", Input::KEY_Q));
	_inputStringMap.insert(std::make_pair("KEY_R", Input::KEY_R));
	_inputStringMap.insert(std::make_pair("KEY_S", Input::KEY_S));
	_inputStringMap.insert(std::make_pair("KEY_T", Input::KEY_T));
	_inputStringMap.insert(std::make_pair("KEY_U", Input::KEY_U));
	_inputStringMap.insert(std::make_pair("KEY_V", Input::KEY_V));
	_inputStringMap.insert(std::make_pair("KEY_W", Input::KEY_W));
	_inputStringMap.insert(std::make_pair("KEY_X", Input::KEY_X));
	_inputStringMap.insert(std::make_pair("KEY_Y", Input::KEY_Y));
	_inputStringMap.insert(std::make_pair("KEY_Z", Input::KEY_Z));
}