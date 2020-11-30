#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:print")
	{
		// Validate amount of arguments
		if (_validateListAmount(arguments, 1))
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

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			_sceneEditor.loadSceneFromFile(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:scene_clear") // Clear all entities and reset scene
	{
		if (_validateListAmount(arguments, 0) && _validateListTypes(arguments, {}))
		{
			_sceneEditor.clearScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_cursor_show") // SHow cursor
	{
		if (_validateListAmount(arguments, 0) && _validateListTypes(arguments, {}))
		{
			_fe3d.misc_showCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_cursor_hide") // Hide cursor
	{
		if (_validateListAmount(arguments, 0) && _validateListTypes(arguments, {}))
		{
			_fe3d.misc_hideCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_time_interval") // Time interval
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getString(), arguments[1].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:misc_substr") // Cut a part from a string
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER, ScriptValueType::INTEGER };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = arguments[0].getString().substr(arguments[1].getInteger(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}

bool ScriptInterpreter::_validateFe3dGameEntity(const string& ID)
{
	if (!_fe3d.gameEntity_isExisting(ID))
	{
		_throwScriptError("game entity with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}