#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:print")
	{
		// Validate amount of arguments
		if (_validateArgumentAmount(arguments, 1))
		{
			// Determine which type of value to print
			if (arguments[0].getType() == ScriptValueType::VEC3)
			{
				_fe3d.logger_throwInfo(_fe3d.misc_vec2str(arguments[0].getVec3()));
			}
			else if (arguments[0].getType() == ScriptValueType::STRING)
			{
				_fe3d.logger_throwInfo(arguments[0].getString());
			}
			else if (arguments[0].getType() == ScriptValueType::DECIMAL)
			{
				_fe3d.logger_throwInfo(arguments[0].getDecimal());
			}
			else if (arguments[0].getType() == ScriptValueType::INTEGER)
			{
				_fe3d.logger_throwInfo(arguments[0].getInteger());
			}
			else if (arguments[0].getType() == ScriptValueType::BOOLEAN)
			{
				_fe3d.logger_throwInfo(arguments[0].getBoolean() ? "true" : "false");
			}

			// Add return value
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:scene_load") // Load specific scene from file
	{
		auto types = { ScriptValueType::STRING };

		if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
		{
			_sceneEditor.loadSceneFromFile(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:scene_clear") // Clear all entities and reset scene
	{
		if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_sceneEditor.clearScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_cursor_show") // SHow cursor
	{
		if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.misc_showCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_cursor_hide") // Hide cursor
	{
		if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.misc_hideCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_time_interval") // Time interval
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER };

		if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getString(), arguments[1].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}