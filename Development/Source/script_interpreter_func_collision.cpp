#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dCollisionFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_game_entity") // Raycasting into a single gameEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			auto result = _fe3d.collision_checkCursorInEntity(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else if (functionName == "fe3d:raycast_game_entity_group") // Raycasting into multiple gameEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		if (_validateListAmount(arguments, types.size()) && _validateListTypes(arguments, types))
		{
			// Find aabbEntity ID
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto result = _fe3d.collision_checkCursorInEntities(searchID);
			
			// Retrieve bound gameEntity ID
			if (!result.empty() && (_fe3d.aabbEntity_getParentType(result) == AabbParentType::GAME_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
			return true;
		}
	}
	else if (functionName == "fe3d:raycast_game_entities") // Raycasting into all gameEntities
	{
		if (_validateListAmount(arguments, 0) && _validateListTypes(arguments, {}))
		{
			auto result = _fe3d.collision_checkCursorInAny();

			// Check if AABB entity has a parent GAME entity
			if (!result.empty() && _fe3d.aabbEntity_getParentType(result) == AabbParentType::GAME_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
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