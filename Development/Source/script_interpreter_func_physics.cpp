#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dPhysicsFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_model") // Raycasting into a single gameEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntity ID & AABB part ID

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.collision_checkCursorInEntity(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:raycast_model_group") // Raycasting into multiple gameEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
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
		}
	}
	else if (functionName == "fe3d:raycast_models") // Raycasting into all gameEntities
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.collision_checkCursorInAny();

			// Check if AABB entity has a parent GAME entity
			if (!result.empty() && _fe3d.aabbEntity_getParentType(result) == AabbParentType::GAME_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_enable_camera_terrain_response") // Enable collision response between camera & terrain
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableCameraTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_terrain_response") // Disable collision response between camera & terrain
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_enableCameraTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_is_camera_under_terrain") // Check if camera is under terrain point
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			bool result = _fe3d.collision_checkTerrainWithCamera();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_enable_camera_aabb_response") // Enable collision response between camera & AABB
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_enableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_aabb_response") // Disable collision response between camera & AABB
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_disableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_aabb") // Check if camera collided with a gameEntity AABB
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntity ID & AABB part ID

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto result = _fe3d.collision_checkEntitiesWithCamera(searchID);

			// Retrieve bound gameEntity ID
			if (!result.empty() && (_fe3d.aabbEntity_getParentType(result) == AabbParentType::GAME_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}