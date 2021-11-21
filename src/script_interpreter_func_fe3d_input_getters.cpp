#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dInputGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:input_is_key_down")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
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
		_throwScriptError("cannot access `fe3d:input` functionality as a networking server!");
	}

	return true;
}