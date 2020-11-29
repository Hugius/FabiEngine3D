#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dCollisionFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_in_entity") // Raycasting into a single entity
	{
		auto types = { ScriptValueType::STRING };

		if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.collision_checkCursorInEntity(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:raycast_in_entities") // Raycasting into a multiple entities
	{
		auto types = { ScriptValueType::STRING };

		if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.collision_checkCursorInEntities(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
			return true;
		}
	}
	else if (functionName == "fe3d:raycast_in_any") // Raycasting into all entities
	{
		if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.collision_checkCursorInAny();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
			return true;
		}
	}
	else
	{
		return false;
	}
}