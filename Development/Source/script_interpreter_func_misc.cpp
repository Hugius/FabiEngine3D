#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:print")
	{
		// Validate amount of arguments
		if (_validateListValueAmount(arguments, 1))
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
		}
	}
	else if (functionName == "fe3d:scene_load") // Load specific scene from file
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_sceneEditor.loadSceneFromFile(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:scene_clear") // Clear all entities and reset scene
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_sceneEditor.clearScene();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_show_cursor") // Show cursor
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_showCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_hide_cursor") // Hide cursor
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_hideCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_time_interval") // Time interval
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getString(), arguments[1].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:misc_string_part") // Cut a part from a string
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER, ScriptValueType::INTEGER };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = arguments[0].getString().substr(arguments[1].getInteger(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:misc_list_size") // Get the size of a list variable
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto nameString = arguments[0].getString();

			// Check if variable exists
			if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
			{
				_throwScriptError("list variable \"" + nameString + "\" not found!");
			}

			// Check if variable is a list
			auto listVariable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);
			if (listVariable.getType() == ScriptVariableType::SINGLE)
			{
				_throwScriptError("variable \"" + nameString + "\" is not a list!");
			}

			// Return list size
			auto result = listVariable.getValueCount();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
		}
	}
	else if (functionName == "fe3d:misc_set_fog_min_distance") // Set fog mindistance
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(arguments[0].getDecimal(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogDefaultFactor(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_get_fog_min_distance") // Get fog mindistance
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMinDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:misc_set_fog_max_distance") // Set fog max distance
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogDefaultFactor(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_get_fog_max_distance") // Get fog max distance
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMaxDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL));
		}
	}
	else if (functionName == "fe3d:misc_set_fog_default_factor") // Set fog default factor
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_get_fog_default_factor") // Get fog defaultfactor
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogDefaultFactor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL));
		}
	}
	else if (functionName == "fe3d:misc_set_fog_color") // Set fog color
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogDefaultFactor(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:misc_get_fog_color") // Get fog color
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3));
		}
	}
	else
	{
		return false;
	}

	return true;
}