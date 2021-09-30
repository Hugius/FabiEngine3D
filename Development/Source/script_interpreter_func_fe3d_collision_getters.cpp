#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dCollisionGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:collision_is_camera_under_terrain")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			bool result = _fe3d.collision_checkCameraWithTerrain();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_model")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntity ID + aabbEntity part ID + direction

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[2].getString() != "X" && arguments[2].getString() != "Y" && 
				arguments[2].getString() != "Z" && arguments[2].getString() != "")
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithEntities(arguments[0].getString());

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has model parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) && 
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
					if ((directionX && arguments[2].getString() == "X") ||
						(directionY && arguments[2].getString() == "Y") ||
						(directionZ && arguments[2].getString() == "Z") ||
						((directionX || directionY || directionZ) && arguments[2].getString().empty()))
					{
						if (arguments[1].getString().empty()) // No specific AABB part
						{
							result = _fe3d.aabbEntity_getParentID(foundAabbID);
						}
						else // Specific AABB part
						{
							// Extract AABB part ID
							string partID = foundAabbID;
							reverse(partID.begin(), partID.end());
							partID = partID.substr(0, partID.find('@'));
							reverse(partID.begin(), partID.end());

							// Check if AABB part ID's match
							if (partID == arguments[1].getString())
							{
								result = _fe3d.aabbEntity_getParentID(foundAabbID);
							}
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_models")
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[0].getString() != "X" && arguments[0].getString() != "Y" &&
				arguments[0].getString() != "Z" && arguments[0].getString() != "")
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has model parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) && 
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
					if ((directionX && arguments[0].getString() == "X") ||
						(directionY && arguments[0].getString() == "Y") ||
						(directionZ && arguments[0].getString() == "Z") ||
						((directionX || directionY || directionZ) && arguments[0].getString().empty()))
					{
						result = _fe3d.aabbEntity_getParentID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_billboard")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[1].getString() != "X" && arguments[1].getString() != "Y" &&
				arguments[1].getString() != "Z" && arguments[1].getString() != "")
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithEntities(arguments[0].getString());

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has billboard parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
					if ((directionX && arguments[1].getString() == "X") ||
						(directionY && arguments[1].getString() == "Y") ||
						(directionZ && arguments[1].getString() == "Z") ||
						((directionX || directionY || directionZ) && arguments[1].getString().empty()))
					{
						result = _fe3d.aabbEntity_getParentID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_billboards")
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[0].getString() != "X" && arguments[0].getString() != "Y" &&
				arguments[0].getString() != "Z" && arguments[0].getString() != "")
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has billboard parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
					if ((directionX && arguments[0].getString() == "X") ||
						(directionY && arguments[0].getString() == "Y") ||
						(directionZ && arguments[0].getString() == "Z") ||
						((directionX || directionY || directionZ) && arguments[0].getString().empty()))
					{
						result = _fe3d.aabbEntity_getParentID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_aabb")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // aabbEntity ID + Direction

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[1].getString() != "X" && arguments[1].getString() != "Y" && 
				arguments[1].getString() != "Z" && arguments[1].getString() != "")
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Validate existing aabbEntity ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Temporary values
				bool result = false;

				// Check if requested aabbEntity is existing
				if (_fe3d.aabbEntity_isExisting(arguments[0].getString()))
				{
					// Check if requested aabbEntity does not have a parent
					if (!_fe3d.aabbEntity_hasParent(arguments[0].getString()))
					{
						// Check direction
						auto directionX = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString(), Direction::X);
						auto directionY = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString(), Direction::Y);
						auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString(), Direction::Z);
						if ((directionX && arguments[1].getString() == "X") ||
							(directionY && arguments[1].getString() == "Y") ||
							(directionZ && arguments[1].getString() == "Z") ||
							((directionX || directionY || directionZ) && arguments[1].getString().empty()))
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
	else if (functionName == "fe3d:collision_check_camera_aabbs")
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[0].getString() != "X" && arguments[0].getString() != "Y" &&
				arguments[0].getString() != "Z" && arguments[0].getString() != "")
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			bool result = false;
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if found and requested aabbEntity has no parent
			if (!foundAabbID.empty() && !_fe3d.aabbEntity_hasParent(foundAabbID))
			{
				// Check direction
				auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
				auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
				auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
				if ((directionX && arguments[0].getString() == "X") ||
					(directionY && arguments[0].getString() == "Y") ||
					(directionZ && arguments[0].getString() == "Z") ||
					((directionX || directionY || directionZ) && arguments[0].getString().empty()))
				{
					result = true;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_models")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			if (arguments[1].getString().empty()) // Check all AABB parts of self entity
			{
				// Get part IDs
				for (const auto& selfSearchID : _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::MODEL_ENTITY))
				{
					// Find aabbEntity ID
					string otherSearchID = arguments[2].getString();
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

					// Check if AABB found
					if (!foundAabbID.empty())
					{
						// Check if AABB has modelEntity parent
						if (_fe3d.aabbEntity_hasParent(foundAabbID) && 
							(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
						{
							if (arguments[1].getString().empty()) // No specific AABB part
							{
								result = foundAabbID;
							}
							else // Specific AABB part
							{
								// Extract AABB part ID
								string partID = foundAabbID;
								reverse(partID.begin(), partID.end());
								partID = partID.substr(0, partID.find('@'));
								reverse(partID.begin(), partID.end());

								// Check if AABB part ID's match
								if (partID == arguments[1].getString())
								{
									result = foundAabbID;
								}
							}

							break;
						}
					}
				}
			}
			else // Check specific AABB part of self entity
			{
				// Check if self aabbEntity entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				string otherSearchID = arguments[2].getString();
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

				// Check if AABB found
				if (!foundAabbID.empty())
				{
					// Check if AABB has modelEntity parent
					if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
						(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
					{
						if (arguments[1].getString().empty()) // No specific AABB part
						{
							result = foundAabbID;
						}
						else // Specific AABB part
						{
							// Extract AABB part ID
							string partID = foundAabbID;
							reverse(partID.begin(), partID.end());
							partID = partID.substr(0, partID.find('@'));
							reverse(partID.begin(), partID.end());

							// Check if AABB part ID's match
							if (partID == arguments[1].getString())
							{
								result = foundAabbID;
							}
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_billboards")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (const auto& selfSearchID : _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::BILLBOARD_ENTITY))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

					// Check if AABB found
					if (!foundAabbID.empty())
					{
						// Check if AABB has billboardEntity parent
						if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
							(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
						{
							result = foundAabbID;
							break;
						}
					}
				}
			}
			else
			{
				// Check if self aabbEntity entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

				// Check if AABB found
				if (!foundAabbID.empty())
				{
					// Check if AABB has billboardEntity parent
					if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
						(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
					{
						result = foundAabbID;
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_aabbs")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING,ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (const auto& selfSearchID : _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::MODEL_ENTITY))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

					// Check if AABB found
					if (!foundAabbID.empty())
					{
						// Check if AABB does not have a parent
						if (!_fe3d.aabbEntity_hasParent(foundAabbID))
						{
							result = foundAabbID;
							break;
						}
					}
				}
			}
			else
			{
				// Check if self aabbEntity entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

				// Check if AABB found
				if (!foundAabbID.empty())
				{
					// Check if AABB does not have a parent
					if (!_fe3d.aabbEntity_hasParent(foundAabbID))
					{
						result = foundAabbID;
					}
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

	// Cannot execute collision functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as a networking server!");
	}

	return true;
}