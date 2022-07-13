#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:collision_check_camera_terrain")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_checkCameraWithTerrain();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
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

							if(args[0]->getString() == subAabbId)
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
	else if(functionName == "fe3d:collision_check_camera_model")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(args[1]->getString().empty())
				{
					bool result = false;

					for(const auto & aabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
					{
						if(args[2]->getString().empty())
						{
							if(_fe3d->collision_checkCameraWithAabb(aabbId))
							{
								result = true;

								break;
							}
						}
						else if(args[2]->getString() == "X")
						{
							if(_fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::X))
							{
								result = true;

								break;
							}
						}
						else if(args[2]->getString() == "Y")
						{
							if(_fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Y))
							{
								result = true;

								break;
							}
						}
						else if(args[2]->getString() == "Z")
						{
							if(_fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Z))
							{
								result = true;

								break;
							}
						}
						else
						{
							_throwRuntimeError("direction is invalid");

							return true;
						}
					}

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else
				{
					const auto aabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

					if(_validateFe3dAabb(aabbId, false))
					{
						if(args[2]->getString().empty())
						{
							const auto result = _fe3d->collision_checkCameraWithAabb(aabbId);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else if(args[2]->getString() == "X")
						{
							const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::X);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else if(args[2]->getString() == "Y")
						{
							const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Y);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else if(args[2]->getString() == "Z")
						{
							const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Z);

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
	}
	else if(functionName == "fe3d:collision_check_camera_quad3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto aabbId = ("quad3d@" + args[0]->getString());

				if(_validateFe3dAabb(aabbId, false))
				{
					if(args[1]->getString().empty())
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "X")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Y")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Z")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Z);

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
				const auto aabbId = ("text3d@" + args[0]->getString());

				if(_validateFe3dAabb(aabbId, false))
				{
					if(args[1]->getString().empty())
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "X")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Y")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Z")
					{
						const auto result = _fe3d->collision_checkCameraWithAabb(aabbId, DirectionType::Z);

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
	else if(functionName == "fe3d:collision_check_model_models")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				bool result = false;

				for(const auto & aabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
				{
					if(!_fe3d->collision_checkAabbWithAabbs(aabbId).empty())
					{
						result = true;

						break;
					}
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_quad3d_quad3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				bool result = false;

				for(const auto & aabbId : _fe3d->quad3d_getChildAabbIds(args[0]->getString()))
				{
					if(!_fe3d->collision_checkAabbWithAabbs(aabbId).empty())
					{
						result = true;

						break;
					}
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_text3d_text3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				bool result = false;

				for(const auto & aabbId : _fe3d->text3d_getChildAabbIds(args[0]->getString()))
				{
					if(!_fe3d->collision_checkAabbWithAabbs(aabbId).empty())
					{
						result = true;

						break;
					}
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_aabb_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				const auto result = !_fe3d->collision_checkAabbWithAabbs(args[0]->getString()).empty();

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_model_model")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dModel(args[2]->getString(), false))
			{
				vector<string> firstAabbIds = {};
				vector<string> secondAabbIds = {};

				if(args[1]->getString().empty())
				{
					for(const auto & aabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
					{
						firstAabbIds.push_back(aabbId);
					}
				}
				else
				{
					const auto aabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

					if(_validateFe3dAabb(aabbId, false))
					{
						firstAabbIds.push_back(aabbId);
					}
				}

				if(args[3]->getString().empty())
				{
					for(const auto & aabbId : _fe3d->model_getChildAabbIds(args[2]->getString()))
					{
						secondAabbIds.push_back(aabbId);
					}
				}
				else
				{
					const auto aabbId = ("model@" + args[2]->getString() + "@" + args[3]->getString());

					if(_validateFe3dAabb(aabbId, false))
					{
						secondAabbIds.push_back(aabbId);
					}
				}

				bool result = false;

				for(const auto & firstAabbId : firstAabbIds)
				{
					for(const auto & secondAabbId : secondAabbIds)
					{
						if(_fe3d->collision_checkAabbWithAabb(firstAabbId, secondAabbId))
						{
							result = true;

							break;
						}
					}
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_quad3d_quad3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				const auto firstAabbId = ("quad3d@" + args[0]->getString());
				const auto secondAabbId = ("quad3d@" + args[1]->getString());

				if(_validateFe3dAabb(firstAabbId, false) && _validateFe3dAabb(secondAabbId, false))
				{
					const auto result = _fe3d->collision_checkAabbWithAabb(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_text3d_text3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false) && _validateFe3dText3d(args[1]->getString(), false))
			{
				const auto firstAabbId = ("text3d@" + args[0]->getString());
				const auto secondAabbId = ("text3d@" + args[1]->getString());

				if(_validateFe3dAabb(firstAabbId, false) && _validateFe3dAabb(secondAabbId, false))
				{
					const auto result = _fe3d->collision_checkAabbWithAabb(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_aabb_aabb")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false) && _validateFe3dAabb(args[1]->getString(), false))
			{
				const auto result = _fe3d->collision_checkAabbWithAabb(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
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