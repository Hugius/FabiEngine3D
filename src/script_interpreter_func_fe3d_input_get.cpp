#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dInputGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:input_is_mouse_scrolled")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = _fe3d->input_isMouseScrolled(mouse_wheel_typeS.at(args[0]->getString()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:input_is_mouse_held")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateMouseInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isMouseHeld(mouse_button_typeS.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_mouse_pressed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateMouseInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isMousePressed(mouse_button_typeS.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_mouse_toggled")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateMouseInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isMouseToggled(mouse_button_typeS.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	if(functionName == "fe3d:input_is_keyboard_held")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateKeyInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isKeyboardHeld(keyboard_key_typeS.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_keyboard_pressed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateKeyInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isKeyboardPressed(keyboard_key_typeS.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_keyboard_toggled")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateKeyInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isKeyboardToggled(keyboard_key_typeS.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:input` functionality as a networking server");
		return true;
	}

	return true;
}