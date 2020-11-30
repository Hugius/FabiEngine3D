#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dInputFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:input_key_down") // Hold keyboard key down
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.input_getKeyDown(_keyInputStringMap.at(arguments[0].getString()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:input_key_pressed") // Press keyboard key
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.input_getKeyPressed(_keyInputStringMap.at(arguments[0].getString()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:input_key_toggled") // Togglepress keyboard key
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.input_getKeyToggled(_keyInputStringMap.at(arguments[0].getString()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:input_mouse_down") // Hold mouse button down
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.input_getMouseDown(_mouseInputStringMap.at(arguments[0].getString()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:input_mouse_pressed") // Press mouse
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.input_getMousePressed(_mouseInputStringMap.at(arguments[0].getString()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:input_mouse_toggled") // Togglepress mouse
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.input_getMouseToggled(_mouseInputStringMap.at(arguments[0].getString()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:input_mousewheel_direction") // Mousewheel direction
	{
		if (_validateListAmount(arguments, 0) && _validateListTypes(arguments, {}))
		{
			auto result = _fe3d.input_getMouseWheelY();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}