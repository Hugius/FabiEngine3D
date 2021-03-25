#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dRaycastFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_enable_terrain_positioning") // Enable raycasting
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }; // Distance + precision

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.misc_enableTerrainRaycasting(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:raycast_disable_terrain_positioning") // Disable raycasting
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_disableTerrainRaycasting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:raycast_get_vector") // Get the raycast vector
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.misc_getRaycastVector();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_get_position_on_terrain") // Get the cursor position on the terrain
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.misc_getRaycastPositionOnTerrain();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_is_position_on_terrain_valid") // Check if the position on the terrain is valid
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.misc_isRaycastPositionOnTerrainValid();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_into_model") // Raycasting into multiple modelEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // ModelEntityID + aabbPartID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[2].getBoolean()).first;

			// Retrieve bound modelEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
			{
				if (arguments[1].getString().empty()) // No specific AABB part
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
				else // Specific AABB part
				{
					// Extract AABB part ID
					string partID = foundAabbID;
					std::reverse(partID.begin(), partID.end());
					partID = partID.substr(0, partID.find('@'));
					std::reverse(partID.begin(), partID.end());

					// Check if AABB part ID's match
					if (partID == arguments[1].getString())
					{
						result = _fe3d.aabbEntity_getParentID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_model_distance")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // ModelEntityID + aabbPartID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[2].getBoolean());
			string foundAabbID = intersection.first;
			float foundDistance = intersection.second;

			// Retrieve bound modelEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
			{
				if (arguments[1].getString().empty()) // No specific AABB part
				{
					result = foundDistance;
				}
				else // Specific AABB part
				{
					// Extract AABB part ID
					string partID = foundAabbID;
					std::reverse(partID.begin(), partID.end());
					partID = partID.substr(0, partID.find('@'));
					std::reverse(partID.begin(), partID.end());

					// Check if AABB part ID's match
					if (partID == arguments[1].getString())
					{
						result = foundDistance;
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_models")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if aabbEntity entity has a parent modelEntity
			if (!foundAabbID.empty() && _fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_models_distance")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.collision_checkCursorInAny();

			// Check if aabbEntity entity has a parent modelEntity
			if (!intersection.first.empty() && _fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::MODEL_ENTITY)
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean()).first;

			// Retrieve bound billboardEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if aabbEntity entity has a parent billboardEntity
			if (!foundAabbID.empty() && _fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard_distance")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean());

			// Retrieve bound billboardEntity ID
			if (!intersection.first.empty() && (_fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::BILLBOARD_ENTITY))
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards_distance")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.collision_checkCursorInAny();

			// Check if aabbEntity entity has a parent billboardEntity
			if (!intersection.first.empty() && _fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::BILLBOARD_ENTITY)
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}