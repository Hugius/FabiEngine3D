#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:collision_is_camera_under_terrain")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_checkCameraWithTerrain();

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[2].getString() != "X" && args[2].getString() != "Y" &&
			   args[2].getString() != "Z" && !args[2].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			string result = "";
			auto foundAabbID = _fe3d->collision_checkCameraWithEntities(args[0].getString());

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) &&
				   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					auto directionX = _fe3d->collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
					auto directionY = _fe3d->collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
					auto directionZ = _fe3d->collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
					if((directionX && args[2].getString() == "X") ||
					   (directionY && args[2].getString() == "Y") ||
					   (directionZ && args[2].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[2].getString().empty()))
					{
						if(args[1].getString().empty())
						{
							result = _fe3d->aabb_getParentEntityID(foundAabbID);
						}
						else
						{
							string partID = foundAabbID;
							reverse(partID.begin(), partID.end());
							partID = partID.substr(0, partID.find('@'));
							reverse(partID.begin(), partID.end());

							if(partID == args[1].getString())
							{
								result = _fe3d->aabb_getParentEntityID(foundAabbID);
							}
						}
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_models")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString() != "X" && args[0].getString() != "Y" &&
			   args[0].getString() != "Z" && !args[0].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			string result = "";
			auto foundAabbID = _fe3d->collision_checkCameraWithAny();

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) &&
				   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					auto directionX = _fe3d->collision_checkCameraWithAnyDirection(Direction::X);
					auto directionY = _fe3d->collision_checkCameraWithAnyDirection(Direction::Y);
					auto directionZ = _fe3d->collision_checkCameraWithAnyDirection(Direction::Z);
					if((directionX && args[0].getString() == "X") ||
					   (directionY && args[0].getString() == "Y") ||
					   (directionZ && args[0].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[0].getString().empty()))
					{
						result = _fe3d->aabb_getParentEntityID(foundAabbID);
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3d")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[1].getString() != "X" && args[1].getString() != "Y" &&
			   args[1].getString() != "Z" && !args[1].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			string result = "";
			auto foundAabbID = _fe3d->collision_checkCameraWithEntities(args[0].getString());

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) &&
				   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::QUAD3D))
				{
					auto directionX = _fe3d->collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
					auto directionY = _fe3d->collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
					auto directionZ = _fe3d->collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
					if((directionX && args[1].getString() == "X") ||
					   (directionY && args[1].getString() == "Y") ||
					   (directionZ && args[1].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[1].getString().empty()))
					{
						result = _fe3d->aabb_getParentEntityID(foundAabbID);
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3ds")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString() != "X" && args[0].getString() != "Y" &&
			   args[0].getString() != "Z" && !args[0].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			string result = "";
			auto foundAabbID = _fe3d->collision_checkCameraWithAny();

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) &&
				   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::QUAD3D))
				{
					auto directionX = _fe3d->collision_checkCameraWithAnyDirection(Direction::X);
					auto directionY = _fe3d->collision_checkCameraWithAnyDirection(Direction::Y);
					auto directionZ = _fe3d->collision_checkCameraWithAnyDirection(Direction::Z);
					if((directionX && args[0].getString() == "X") ||
					   (directionY && args[0].getString() == "Y") ||
					   (directionZ && args[0].getString() == "Z") ||
					   ((directionX || directionY || directionZ) && args[0].getString().empty()))
					{
						result = _fe3d->aabb_getParentEntityID(foundAabbID);
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabb")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(args[1].getString() != "X" && args[1].getString() != "Y" &&
				   args[1].getString() != "Z" && !args[1].getString().empty())
				{
					_throwScriptError("invalid direction argument!");
					return true;
				}

				bool result = false;

				if(_fe3d->aabb_isExisting(args[0].getString()))
				{
					if(!_fe3d->aabb_hasParent(args[0].getString()))
					{
						auto directionX = _fe3d->collision_checkCameraWithEntityDirection(args[0].getString(), Direction::X);
						auto directionY = _fe3d->collision_checkCameraWithEntityDirection(args[0].getString(), Direction::Y);
						auto directionZ = _fe3d->collision_checkCameraWithEntityDirection(args[0].getString(), Direction::Z);
						if((directionX && args[1].getString() == "X") ||
						   (directionY && args[1].getString() == "Y") ||
						   (directionZ && args[1].getString() == "Z") ||
						   ((directionX || directionY || directionZ) && args[1].getString().empty()))
						{
							result = true;
						}
					}
				}

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabbs")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString() != "X" && args[0].getString() != "Y" &&
			   args[0].getString() != "Z" && !args[0].getString().empty())
			{
				_throwScriptError("invalid direction argument!");
				return true;
			}

			bool result = false;
			auto foundAabbID = _fe3d->collision_checkCameraWithAny();

			if(!foundAabbID.empty() && !_fe3d->aabb_hasParent(foundAabbID))
			{
				auto directionX = _fe3d->collision_checkCameraWithAnyDirection(Direction::X);
				auto directionY = _fe3d->collision_checkCameraWithAnyDirection(Direction::Y);
				auto directionZ = _fe3d->collision_checkCameraWithAnyDirection(Direction::Z);
				if((directionX && args[0].getString() == "X") ||
				   (directionY && args[0].getString() == "Y") ||
				   (directionZ && args[0].getString() == "Z") ||
				   ((directionX || directionY || directionZ) && args[0].getString().empty()))
				{
					result = true;
				}
			}

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_model_models")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";

			if(args[1].getString().empty())
			{
				for(const auto& selfSearchID : _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::MODEL))
				{
					string otherSearchID = args[2].getString();
					auto foundAabbID = _fe3d->collision_checkEntityWithEntities(selfSearchID, otherSearchID);

					if(!foundAabbID.empty())
					{
						if(_fe3d->aabb_hasParent(foundAabbID) &&
						   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
						{
							if(args[1].getString().empty())
							{
								result = foundAabbID;
							}
							else
							{
								string partID = foundAabbID;
								reverse(partID.begin(), partID.end());
								partID = partID.substr(0, partID.find('@'));
								reverse(partID.begin(), partID.end());

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
			else
			{
				string selfSearchID = args[0].getString() + (!args[1].getString().empty() ? ("_" + args[1].getString()) : "");
				if(!_fe3d->aabb_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				string otherSearchID = args[2].getString();
				auto foundAabbID = _fe3d->collision_checkEntityWithEntities(selfSearchID, otherSearchID);

				if(!foundAabbID.empty())
				{
					if(_fe3d->aabb_hasParent(foundAabbID) &&
					   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
					{
						if(args[1].getString().empty())
						{
							result = foundAabbID;
						}
						else
						{
							string partID = foundAabbID;
							reverse(partID.begin(), partID.end());
							partID = partID.substr(0, partID.find('@'));
							reverse(partID.begin(), partID.end());

							if(partID == args[1].getString())
							{
								result = foundAabbID;
							}
						}
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_model_quad3ds")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";

			if(args[1].getString().empty())
			{
				for(const auto& selfSearchID : _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::QUAD3D))
				{
					auto foundAabbID = _fe3d->collision_checkEntityWithEntities(selfSearchID, args[2].getString());

					if(!foundAabbID.empty())
					{
						if(_fe3d->aabb_hasParent(foundAabbID) &&
						   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::QUAD3D))
						{
							result = foundAabbID;
							break;
						}
					}
				}
			}
			else
			{
				string selfSearchID = args[0].getString() + (!args[1].getString().empty() ? ("_" + args[1].getString()) : "");
				if(!_fe3d->aabb_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				auto foundAabbID = _fe3d->collision_checkEntityWithEntities(selfSearchID, args[2].getString());

				if(!foundAabbID.empty())
				{
					if(_fe3d->aabb_hasParent(foundAabbID) &&
					   (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::QUAD3D))
					{
						result = foundAabbID;
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:collision_check_model_aabbs")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";

			if(args[1].getString().empty())
			{
				for(const auto& selfSearchID : _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::MODEL))
				{
					auto foundAabbID = _fe3d->collision_checkEntityWithEntities(selfSearchID, args[2].getString());

					if(!foundAabbID.empty())
					{
						if(!_fe3d->aabb_hasParent(foundAabbID))
						{
							result = foundAabbID;
							break;
						}
					}
				}
			}
			else
			{
				string selfSearchID = args[0].getString() + (!args[1].getString().empty() ? ("_" + args[1].getString()) : "");
				if(!_fe3d->aabb_isExisting(selfSearchID))
				{
					_throwScriptError("requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				auto foundAabbID = _fe3d->collision_checkEntityWithEntities(selfSearchID, args[2].getString());

				if(!foundAabbID.empty())
				{
					if(!_fe3d->aabb_hasParent(foundAabbID))
					{
						result = foundAabbID;
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as networking server!");
	}

	return true;
}