#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto fullAabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

				if(_validateFe3dAabb(fullAabbId, false))
				{
					if(args[2]->getString().empty())
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[2]->getString() == "X")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[2]->getString() == "Y")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[2]->getString() == "Z")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::Z);

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
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto fullAabbId = ("quad3d@" + args[0]->getString());

				if(_validateFe3dAabb(fullAabbId, false))
				{
					if(args[1]->getString().empty())
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "X")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Y")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Z")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::Z);

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
	else if(functionName == "fe3d:collision_check_camera_text3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				const auto fullAabbId = ("text3d@" + args[0]->getString());

				if(_validateFe3dAabb(fullAabbId, false))
				{
					if(args[1]->getString().empty())
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "X")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Y")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Z")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(fullAabbId, DirectionType::Z);

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
	else if(functionName == "fe3d:collision_check_camera_aabb")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(args[1]->getString().empty())
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "X")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), DirectionType::X);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Y")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), DirectionType::Y);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Z")
				{
					const auto result = _fe3d->collision_checkCameraWithAabb(args[0]->getString(), DirectionType::Z);

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
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::MODEL)
					{
						if(args[0]->getString().empty())
						{
							const auto result = _fe3d->aabb_getParentId(aabbId);

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
						}
						else
						{
							const auto rawAabbId = aabbId.substr(string("model@").size());
							const auto subAabbId = rawAabbId.substr(rawAabbId.find('@'));

							if(subAabbId == args[0]->getString())
							{
								const auto result = _fe3d->aabb_getParentId(aabbId);

								returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
							}
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::QUAD3D)
					{
						const auto result = _fe3d->aabb_getParentId(aabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_text3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::TEXT3D)
					{
						const auto result = _fe3d->aabb_getParentId(aabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_checkCameraWithAabbs(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
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