#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:collision_is_camera_terrain_response_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_isCameraTerrainResponseEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_get_camera_terrain_response_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_getCameraTerrainResponseHeight();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:collision_get_camera_terrain_response_speed")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_getCameraTerrainResponseSpeed();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:collision_is_camera_aabb_response_enabled_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_isCameraAabbResponseEnabledX();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_is_camera_aabb_response_enabled_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_isCameraAabbResponseEnabledY();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_is_camera_aabb_response_enabled_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_isCameraAabbResponseEnabledZ();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_terrain")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_checkCameraWithTerrain();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dAabb((args[0]->getString() + "@" + args[1]->getString())))
				{
					if(args[2]->getString().empty())
					{
						const auto result = _fe3d->collision_checkCameraWithAabb((args[0]->getString() + "@" + args[1]->getString()));

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[2]->getString() == "X")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb((args[0]->getString() + "@" + args[1]->getString()), Direction::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[2]->getString() == "Y")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb((args[0]->getString() + "@" + args[1]->getString()), Direction::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[2]->getString() == "Z")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb((args[0]->getString() + "@" + args[1]->getString()), Direction::Z);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else
					{
						_throwRuntimeError("direction is invalid");
						return true;
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3d")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				if(args[1]->getString().empty())
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "X")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::X);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Y")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::Y);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Z")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::Z);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else
				{
					_throwRuntimeError("direction is invalid");
					return true;
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_text3d")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				if(args[1]->getString().empty())
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "X")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::X);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Y")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::Y);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Z")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::Z);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else
				{
					_throwRuntimeError("direction is invalid");
					return true;
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabb")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(args[1]->getString().empty())
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "X")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::X);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Y")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::Y);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Z")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), Direction::Z);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else
				{
					_throwRuntimeError("direction is invalid");
					return true;
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_models")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds;

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");
				return true;
			}

			for(const auto& aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId) && (_fe3d->aabb_getParentType(aabbId) == AabbParentType::MODEL))
				{
					const auto modelId = aabbId.substr(0, aabbId.find('@'));

					if(args[0]->getString().empty())
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, modelId));
					}
					else
					{
						auto partId = aabbId;
						reverse(partId.begin(), partId.end());
						partId = partId.substr(0, partId.find('@'));
						reverse(partId.begin(), partId.end());

						if(partId == args[0]->getString())
						{
							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, modelId));
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3ds")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds;

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");
				return true;
			}

			for(const auto& aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId) && (_fe3d->aabb_getParentType(aabbId) == AabbParentType::QUAD3D))
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, aabbId));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_text3ds")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds;

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");
				return true;
			}

			for(const auto& aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId) && (_fe3d->aabb_getParentType(aabbId) == AabbParentType::TEXT3D))
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, aabbId));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabbs")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds;

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(Direction::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");
				return true;
			}

			for(const auto& aabbId : aabbIds)
			{
				if(!_fe3d->aabb_hasParent(aabbId))
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, aabbId));
				}
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:collision` functionality as a networking server");
		return true;
	}

	return true;
}