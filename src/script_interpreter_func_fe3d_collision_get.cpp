#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:collision_is_camera_under_terrain")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d.collision_checkCameraWithTerrain();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate direction
			if(args[2].getString() != "X" && args[2].getString() != "Y" &&
			   args[2].getString() != "Z" && !args[2].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithEntities(args[0].getString());

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has model parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
					if((directionX && args[2].getString() == "X") ||
					   (directionY && args[2].getString() == "Y") ||
					   (directionZ && args[2].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[2].getString().empty()))
					{
						if(args[1].getString().empty()) // No specific AABB part
						{
							result = _fe3d.aabb_getParentEntityID(foundAabbID);
						}
						else // Specific AABB part
						{
							// Extract AABB part ID
							string partID = foundAabbID;
							reverse(partID.begin(), partID.end());
							partID = partID.substr(0, partID.find('@'));
							reverse(partID.begin(), partID.end());

							// Check if AABB part IDs match
							if(partID == args[1].getString())
							{
								result = _fe3d.aabb_getParentEntityID(foundAabbID);
							}
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_models")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate direction
			if(args[0].getString() != "X" && args[0].getString() != "Y" &&
			   args[0].getString() != "Z" && !args[0].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has model parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
					if((directionX && args[0].getString() == "X") ||
					   (directionY && args[0].getString() == "Y") ||
					   (directionZ && args[0].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[0].getString().empty()))
					{
						result = _fe3d.aabb_getParentEntityID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate direction
			if(args[1].getString() != "X" && args[1].getString() != "Y" &&
			   args[1].getString() != "Z" && !args[1].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithEntities(args[0].getString());

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has billboard parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::BILLBOARD))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
					if((directionX && args[1].getString() == "X") ||
					   (directionY && args[1].getString() == "Y") ||
					   (directionZ && args[1].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[1].getString().empty()))
					{
						result = _fe3d.aabb_getParentEntityID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_billboards")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate direction
			if(args[0].getString() != "X" && args[0].getString() != "Y" &&
			   args[0].getString() != "Z" && !args[0].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			string result = "";
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has billboard parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::BILLBOARD))
				{
					// Check direction
					auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
					auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
					auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
					if((directionX && args[0].getString() == "X") ||
					   (directionY && args[0].getString() == "Y") ||
					   (directionZ && args[0].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[0].getString().empty()))
					{
						result = _fe3d.aabb_getParentEntityID(foundAabbID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabb")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Validate direction
				if(args[1].getString() != "X" && args[1].getString() != "Y" &&
				   args[1].getString() != "Z" && !args[1].getString().empty())
				{
					_throwScriptError("invalid direction argument!");
					return true;
				}

				// Temporary values
				bool result = false;

				// Check if requested aabbEntity existing
				if(_fe3d.aabb_isExisting(args[0].getString()))
				{
					// Check if requested aabbEntity does not have a parent
					if(!_fe3d.aabb_hasParent(args[0].getString()))
					{
						// Check direction
						auto directionX = _fe3d.collision_checkCameraWithEntityDirection(args[0].getString(), Direction::X);
						auto directionY = _fe3d.collision_checkCameraWithEntityDirection(args[0].getString(), Direction::Y);
						auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(args[0].getString(), Direction::Z);
						if((directionX && args[1].getString() == "X") ||
						   (directionY && args[1].getString() == "Y") ||
						   (directionZ && args[1].getString() == "Z") ||
						   ((directionX || directionY || directionZ) && args[1].getString().empty()))
						{
							result = true;
						}
					}
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabbs")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate direction
			if(args[0].getString() != "X" && args[0].getString() != "Y" &&
			   args[0].getString() != "Z" && !args[0].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			// Find aabbEntity
			bool result = false;
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if found and requested aabbEntity has no parent
			if(!foundAabbID.empty() && !_fe3d.aabb_hasParent(foundAabbID))
			{
				// Check direction
				auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
				auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
				auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
				if((directionX && args[0].getString() == "X") ||
				   (directionY && args[0].getString() == "Y") ||
				   (directionZ && args[0].getString() == "Z") ||
				   ((directionX || directionY || directionZ) && args[0].getString().empty()))
				{
					result = true;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_model_models")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			string result = "";

			if(args[1].getString().empty()) // Check all AABB parts of self entity
			{
				// Get part IDs
				for(const auto& selfSearchID : _fe3d.aabb_getChildIDs(args[0].getString(), AabbParentEntityType::MODEL))
				{
					// Find aabbEntity ID
					string otherSearchID = args[2].getString();
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

					// Check if AABB found
					if(!foundAabbID.empty())
					{
						// Check if AABB has modelEntity parent
						if(_fe3d.aabb_hasParent(foundAabbID) &&
						   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
						{
							if(args[1].getString().empty()) // No specific AABB part
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

								// Check if AABB part IDs match
								if(partID == args[1].getString())
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
				string selfSearchID = args[0].getString() + (!args[1].getString().empty() ? ("_" + args[1].getString()) : "");
				if(!_fe3d.aabb_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				string otherSearchID = args[2].getString();
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

				// Check if AABB found
				if(!foundAabbID.empty())
				{
					// Check if AABB has modelEntity parent
					if(_fe3d.aabb_hasParent(foundAabbID) &&
					   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
					{
						if(args[1].getString().empty()) // No specific AABB part
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

							// Check if AABB part IDs match
							if(partID == args[1].getString())
							{
								result = foundAabbID;
							}
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_model_billboards")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if(args[1].getString().empty())
			{
				// Get part IDs
				for(const auto& selfSearchID : _fe3d.aabb_getChildIDs(args[0].getString(), AabbParentEntityType::BILLBOARD))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, args[2].getString());

					// Check if AABB found
					if(!foundAabbID.empty())
					{
						// Check if AABB has billboardEntity parent
						if(_fe3d.aabb_hasParent(foundAabbID) &&
						   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::BILLBOARD))
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
				string selfSearchID = args[0].getString() + (!args[1].getString().empty() ? ("_" + args[1].getString()) : "");
				if(!_fe3d.aabb_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, args[2].getString());

				// Check if AABB found
				if(!foundAabbID.empty())
				{
					// Check if AABB has billboardEntity parent
					if(_fe3d.aabb_hasParent(foundAabbID) &&
					   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::BILLBOARD))
					{
						result = foundAabbID;
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_model_aabbs")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if(args[1].getString().empty())
			{
				// Get part IDs
				for(const auto& selfSearchID : _fe3d.aabb_getChildIDs(args[0].getString(), AabbParentEntityType::MODEL))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, args[2].getString());

					// Check if AABB found
					if(!foundAabbID.empty())
					{
						// Check if AABB does not have a parent
						if(!_fe3d.aabb_hasParent(foundAabbID))
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
				string selfSearchID = args[0].getString() + (!args[1].getString().empty() ? ("_" + args[1].getString()) : "");
				if(!_fe3d.aabb_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, args[2].getString());

				// Check if AABB found
				if(!foundAabbID.empty())
				{
					// Check if AABB does not have a parent
					if(!_fe3d.aabb_hasParent(foundAabbID))
					{
						result = foundAabbID;
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as networking server!");
	}

	return true;
}