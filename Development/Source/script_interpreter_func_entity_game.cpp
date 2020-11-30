#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dGameEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:entity_game_position_set") // Set gameEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::VEC3 };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setPosition(arguments[0].getString(), arguments[1].getVec3());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}

			return true;
		}
	}
	else if (functionName == "fe3d:entity_game_position_get") // Get gameEntity position
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
			
			return true;
		}
	}
	else if (functionName == "fe3d:entity_game_delete") // Delete gameEntity
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
			
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}