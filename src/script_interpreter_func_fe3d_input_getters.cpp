#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dInputGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:input_is_key_down")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateKeyInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_isKeyDown(KEY_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_key_pressed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateKeyInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_isKeyPressed(KEY_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_mouse_down")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateMouseInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_isMouseDown(MOUSE_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_mouse_pressed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateMouseInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_isMousePressed(MOUSE_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_get_mousewheel_direction")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.input_getMouseWheelY();
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute input functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:input` functionality as networking server!");
	}

	return true;
}