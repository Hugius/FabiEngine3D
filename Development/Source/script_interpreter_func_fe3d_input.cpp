#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dInputFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:input_is_key_down") // Hold keyboard key down
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateKeyInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_getKeyDown(KEY_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:input_is_key_pressed") // Press keyboard key
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateKeyInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_getKeyPressed(KEY_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:input_is_key_toggled") // Togglepress keyboard key
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateKeyInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_getKeyToggled(KEY_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:input_is_mouse_down") // Hold mouse button down
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateMouseInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_getMouseDown(MOUSE_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:input_is_mouse_pressed") // Press mouse
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateMouseInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_getMousePressed(MOUSE_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:input_is_mouse_toggled") // Togglepress mouse
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateMouseInputString(arguments[0].getString()))
			{
				auto result = _fe3d.input_getMouseToggled(MOUSE_INPUT_STRING_MAP.at(arguments[0].getString()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:input_get_mousewheel_direction") // Mousewheel direction
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.input_getMouseWheelY();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else
	{
		return false;
	}


	return true;
}