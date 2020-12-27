#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dPhysicsFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_into_model") // Raycasting into multiple gameEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // GameEntityID + AABBpartID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto result = _fe3d.collision_checkCursorInEntities(searchID, arguments[2].getBoolean());

			// Retrieve bound gameEntity ID
			if (!result.empty() && (_fe3d.aabbEntity_getParentType(result) == AabbParentType::GAME_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_models") // Raycasting into all gameEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.collision_checkCursorInAny();

			// Check if AABB entity has a parent gameEntity
			if (!result.empty() && _fe3d.aabbEntity_getParentType(result) == AabbParentType::GAME_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard") // Raycasting into multiple billboardEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			auto result = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean());

			// Retrieve bound billboardEntity ID
			if (!result.empty() && (_fe3d.aabbEntity_getParentType(result) == AabbParentType::BILLBOARD_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(result);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards") // Raycasting into all billboardEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.collision_checkCursorInAny();

			// Check if AABB entity has a parent billboardEntity
			if (!result.empty() && _fe3d.aabbEntity_getParentType(result) == AabbParentType::BILLBOARD_ENTITY)
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

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableCameraTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_terrain_response") // Disable collision response between camera & terrain
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_enableCameraTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_is_camera_under_terrain") // Check if camera is under terrain point
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			bool result = _fe3d.collision_checkCameraWithTerrain();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_set_camera_box") // Save camera box size
	{
		// Bottom top left right front back
		auto types =
		{
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL,
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_setCameraBoxSize(
				arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal(),
				arguments[3].getDecimal(), arguments[4].getDecimal(), arguments[5].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_enable_camera_aabb_response") // Enable collision response between camera & AABB
	{
		// xResponse yResponse zResponse
		auto types =
		{
			ScriptValueType::BOOLEAN, ScriptValueType::BOOLEAN, ScriptValueType::BOOLEAN
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableCameraResponse(arguments[0].getBoolean(), arguments[1].getBoolean(), arguments[2].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_aabb_response") // Disable collision response between camera & AABB
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_disableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_model") // Check if camera collided with a gameEntity AABB group
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntity ID + AABB part ID + Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			string result = "";

			// Find aabbEntity
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto foundAabbID = _fe3d.collision_checkCameraWithEntities(searchID);

			// Retrieve bound gameEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
			{
				// Check direction
				string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				auto direction = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID);
				if ((direction == Direction::X && arguments[2].getString() == "X") ||
					(direction == Direction::Y && arguments[2].getString() == "Y") ||
					(direction == Direction::Z && arguments[2].getString() == "Z") ||
					(direction != Direction::NONE && arguments[2].getString().empty()))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_models") // Check if camera collided with any gameEntity AABB
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			string result = "";

			// Find aabbEntity
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Retrieve bound gameEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
			{
				// Check direction
				auto direction = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID);
				if ((direction == Direction::X && arguments[0].getString() == "X") ||
					(direction == Direction::Y && arguments[0].getString() == "Y") ||
					(direction == Direction::Z && arguments[0].getString() == "Z") ||
					(direction != Direction::NONE && arguments[0].getString().empty()))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_aabb") // Check if camera collided with a specific AABB
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // AABB ID + Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				bool result = false;

				// Check if requested AABB is existing
				if (_fe3d.aabbEntity_isExisting(arguments[0].getString()))
				{
					// Check if requested AABB has no parent
					if (_fe3d.aabbEntity_getParentType(arguments[0].getString()) == AabbParentType::NONE)
					{
						// Check direction
						auto direction = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString());
						if ((direction == Direction::X && arguments[1].getString() == "X") ||
							(direction == Direction::Y && arguments[1].getString() == "Y") ||
							(direction == Direction::Z && arguments[1].getString() == "Z") ||
							(direction != Direction::NONE && arguments[1].getString().empty()))
						{
							result = true;
						}
					}
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:collision_check_camera_aabbs") // Check if camera collided with any AABB
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool result = false;

			// Find aabbEntity
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if found and requested AABB has no parent
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::NONE))
			{
				// Check direction
				auto direction = _fe3d.collision_checkCameraWithAnyDirection();
				if ((direction == Direction::X && arguments[0].getString() == "X") ||
					(direction == Direction::Y && arguments[0].getString() == "Y") ||
					(direction == Direction::Z && arguments[0].getString() == "Z") ||
					(direction != Direction::NONE && arguments[0].getString().empty()))
				{
					result = true;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_models") // Check if gameEntity AABB collided with another gameEntity AABB
	{
		auto types = 
		{ 
			ScriptValueType::STRING, ScriptValueType::STRING, // GameEntity ID + AABB part ID
			ScriptValueType::STRING, ScriptValueType::STRING  // GameEntity ID + AABB part ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			string result = "";

			// Check if no AABB part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (auto& selfSearchID : _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false))
				{
					// Find aabbEntity ID
					string otherSearchID = arguments[2].getString() + (!arguments[3].getString().empty() ? ("_" + arguments[3].getString()) : "");
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

					// Retrieve bound gameEntity ID
					if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
					{
						result = foundAabbID;
						break;
					}
				}
			}
			else
			{
				// Check if self AABB entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("Requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				string otherSearchID = arguments[2].getString() + (!arguments[3].getString().empty() ? ("_" + arguments[3].getString()) : "");
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

				// Retrieve bound gameEntity ID
				if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
				{
					result = foundAabbID;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_billboards") // Check if gameEntity AABB collided with any billboardEntity AABB
	{
		auto types =
		{
			ScriptValueType::STRING, ScriptValueType::STRING, // GameEntity ID + AABB part ID
			ScriptValueType::STRING // BillboardEntity ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			string result = "";

			// Check if no AABB part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (auto& selfSearchID : _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), false, true))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

					// Retrieve bound gameEntity ID
					if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
					{
						result = foundAabbID;
						break;
					}
				}
			}
			else
			{
				// Check if self AABB entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("Requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

				// Retrieve bound gameEntity ID
				if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
				{
					result = foundAabbID;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_aabbs") // Check if gameEntity AABB collided with any AABB
	{
		auto types =
		{
			ScriptValueType::STRING, ScriptValueType::STRING, // GameEntity ID + AABB part ID
			ScriptValueType::STRING // AABB ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			string result = "";

			// Check if no AABB part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (auto& selfSearchID : _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

					// Check if found
					if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::NONE))
					{
						result = foundAabbID;
						break;
					}
				}
			}
			else
			{
				// Check if self AABB entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("Requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

				// Check if found
				if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::NONE))
				{
					result = foundAabbID;
				}
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